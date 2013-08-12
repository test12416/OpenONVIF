#include "sigrlog.h"
#include <remotediscovery.hpp>
#include <WsddRemoteDiscoveryBindingService.h>
#include "wsa.hpp"
#include <assert.h>

class RemoteDiscoveryService :
    public BaseService<RemoteDiscovery, RemoteDiscoveryBindingService>
{
    static const uint TIMEOUT = 5; // second
    static const uint APP_MAX_DELAY = 500;

    template<class T>
    class Arg : public T
    {
    public:
        template<class P>
        Arg(struct soap * soap, const P & arg)
        {
            T::types = arg.Types;
            T::xaddrs = arg.XAddrs;

            T::scopes = NULL;
            if (arg.Scopes != NULL) {
                T::scopes = &scopes_;
                T::scopes->item = arg.Scopes->__item;
                T::scopes->matchBy = arg.Scopes->MatchBy;
            }

            T::endpoint = NULL;
            if (arg.wsa__EndpointReference != NULL) {
                T::endpoint = &endpoint_;

                T::endpoint->address = NULL;
                if (arg.wsa__EndpointReference->Address != NULL) {
                    T::endpoint->address = &arg.wsa__EndpointReference->Address->__item;
                }

                T::endpoint->portType = NULL;
                if (arg.wsa__EndpointReference->PortType != NULL) {
                    T::endpoint->address = &arg.wsa__EndpointReference->PortType->__item;
                }

                T::endpoint->serviceName = NULL;
                if (arg.wsa__EndpointReference->ServiceName != NULL) {
                    T::endpoint->serviceName = &service_;
                    T::endpoint->serviceName->item = arg.wsa__EndpointReference->ServiceName->__item;
                    T::endpoint->serviceName->portName = arg.wsa__EndpointReference->ServiceName->PortName;
                }
            }
        }

    private:
        RemoteDiscovery::Scopes_t scopes_;
        RemoteDiscovery::EndpointReference_t endpoint_;
        RemoteDiscovery::EndpointReference_t::ServiceName service_;
    };

    typedef std::vector<Wsa::Request<wsd__ProbeMatchType> > Matches_t;

public:
    RemoteDiscoveryService() :
        wsa_(RemoteDiscoveryBindingService::soap)
    {
        RemoteDiscoveryBindingService::soap->send_timeout = TIMEOUT;
        RemoteDiscoveryBindingService::soap->recv_timeout = TIMEOUT;
        RemoteDiscoveryBindingService::soap->accept_timeout = TIMEOUT;
    }

    virtual ~RemoteDiscoveryService()
    {
        destroy();
        soap_done(RemoteDiscoveryBindingService::soap);
    }

    virtual struct soap* getSoap()
    {
        return RemoteDiscoveryBindingService::soap;
    }

    virtual RemoteDiscoveryBindingService* copy()
    {
        return NULL;
    }

    virtual int bind(RemoteDiscovery * obj, int port)
    {
        this->p = obj;
        if (port == 0)
            port = 3702;

        soap_mode(RemoteDiscoveryBindingService::soap, SOAP_IO_UDP | SOAP_XML_IGNORENS);

        int socket = RemoteDiscoveryBindingService::bind(NULL, port, 100);
        if (!soap_valid_socket(socket))
            return SOAP_INVALID_SOCKET;

        ip_mreq mcast;
        mcast.imr_multiaddr.s_addr = inet_addr(WSDD_MULTICAT_IP);
        mcast.imr_interface.s_addr = htonl(INADDR_ANY);
        if (setsockopt(socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mcast, sizeof(mcast)) < 0)
            return SOAP_INVALID_SOCKET;

        return socket;
    }

    virtual	int dispatch()
    {
        try {
            static const std::string PROBE_MATCHES = "http://www.onvif.org/ver10/network/wsdl/ProbeMatches";

            int rv = RemoteDiscoveryBindingService::dispatch();
            if (rv != SOAP_OK) {
//                if ((rv == SOAP_NO_METHOD)
//                && (action ? action == PROBE_MATCHES : soap_match_tag(this, tag, "d:ProbeMatches") == 0))
//                {
//                    rv = serveProbeMatches();
//                }

                if (rv == SOAP_USER_ERROR) {
                    soap_closesock(RemoteDiscoveryBindingService::soap);
                    return SOAP_OK;
                }

                RemoteDiscoveryBindingService::soap->error = rv;
                throw SoapException(RemoteDiscoveryBindingService::soap);
            }

        } catch (std::exception & ex) {
            RemoteDiscoveryBindingService::soap_senderfault("RemoteDiscovery", ex.what(), NULL);
            return SOAP_FAULT;
        }

        return SOAP_OK;
    }



    virtual int Hello(wsd__HelloType * wsd__Hello, wsd__ResolveType * wsd__HelloResponse)
    {
        assert(wsd__Hello != NULL && wsd__HelloResponse != NULL);

        if (p != NULL) {
            Arg<RemoteDiscovery::Hello_t> arg(RemoteDiscoveryBindingService::soap, *wsd__Hello);
            arg.version = wsd__Hello->MetadataVersion;
            p->hello(arg);
        }

        wsd__HelloResponse->soap_default(RemoteDiscoveryBindingService::soap);

        return SOAP_USER_ERROR;
    }

    virtual int Bye(wsd__ByeType * wsd__Bye, wsd__ResolveType * dn__ByeResponse)
    {
        assert(wsd__Bye != NULL && dn__ByeResponse != NULL);

        if (p != NULL) {
            Arg<RemoteDiscovery::Bye_t> arg(RemoteDiscoveryBindingService::soap, *wsd__Bye);

            arg.version = wsd__Bye->MetadataVersion ? *wsd__Bye->MetadataVersion : 0;
            p->bye(arg);
        }

        dn__ByeResponse->soap_default(RemoteDiscoveryBindingService::soap);

        return SOAP_USER_ERROR;
    }

    virtual int Probe(wsd__ProbeType * wsd__Probe, wsd__ProbeMatchesType * wsd__ProbeResponse)
    {
        assert(wsd__Probe != NULL && wsd__ProbeResponse != NULL);

        if (p != NULL) {
            RemoteDiscovery::Probe_t arg;
            RemoteDiscovery::Scopes_t scopes;

            arg.types = wsd__Probe->Types;
            arg.scopes = NULL;
            if (wsd__Probe->Scopes != NULL) {
                arg.scopes = &scopes;
                arg.scopes->item = wsd__Probe->Scopes->__item;
                arg.scopes->matchBy = wsd__Probe->Scopes->MatchBy;
            }

            // Header
            std::string relatesTo = soap_header()->wsa__MessageID;
            wsa_.request("", SOAP_NAMESPACE_OF_wsd"/ProbeMatches");
            wsa_.addRelatesTo(relatesTo);
            wsa_.addAppSequence();

            // Body
            wsd__ProbeMatchesType req;
            req.soap_default(RemoteDiscoveryBindingService::soap);

            RemoteDiscovery::ProbeMatches_t items = p->probe(arg);
            matches_.reserve(items.size());

            // Fill the result array wsd__ProbeMatchType, converted from ProbeMatch;
            wsd__ProbeResponse->ProbeMatch.resize(items.size());
            for (size_t i = 0, sz = items.size(); i < sz; ++i) {
                matches_.push_back(Matches_t::value_type(RemoteDiscoveryBindingService::soap, items[i]));
                matches_.back().MetadataVersion = items[i].version;
                wsd__ProbeResponse->ProbeMatch[i] = &matches_.back();
            }

            for (int i = 0; i < 2; ++i) {
                soap_serializeheader(RemoteDiscoveryBindingService::soap);
                wsd__ProbeResponse->soap_serialize(RemoteDiscoveryBindingService::soap);
                if (soap_begin_count(RemoteDiscoveryBindingService::soap))
                    return RemoteDiscoveryBindingService::soap->error;

                if (RemoteDiscoveryBindingService::soap->mode & SOAP_IO_LENGTH) {
                    if (soap_envelope_begin_out(RemoteDiscoveryBindingService::soap)
                     || soap_putheader(RemoteDiscoveryBindingService::soap)
                     || soap_body_begin_out(RemoteDiscoveryBindingService::soap)
                     || wsd__ProbeResponse->soap_put(RemoteDiscoveryBindingService::soap, "wsd:ProbeMatches", "")
                     || soap_body_end_out(RemoteDiscoveryBindingService::soap)
                     || soap_envelope_end_out(RemoteDiscoveryBindingService::soap))
                         return RemoteDiscoveryBindingService::soap->error;
                };
                if (soap_end_count(RemoteDiscoveryBindingService::soap)
                 || soap_response(RemoteDiscoveryBindingService::soap, SOAP_OK)
                 || soap_envelope_begin_out(RemoteDiscoveryBindingService::soap)
                 || soap_putheader(RemoteDiscoveryBindingService::soap)
                 || soap_body_begin_out(RemoteDiscoveryBindingService::soap)
                 || wsd__ProbeResponse->soap_put(RemoteDiscoveryBindingService::soap, "wsd:ProbeMatches", "")
                 || soap_body_end_out(RemoteDiscoveryBindingService::soap)
                 || soap_envelope_end_out(RemoteDiscoveryBindingService::soap)
                 || soap_end_send(RemoteDiscoveryBindingService::soap))
                    return RemoteDiscoveryBindingService::soap->error;
            }
        }

        return SOAP_USER_ERROR;

    }

//private:
//    int serveProbeMatches()
//    {
//        if (p != NULL) {
//            p->probeMatches(RemoteDiscovery::ProbeMatches_t(), std::string());
//        }

//        return SOAP_USER_ERROR;
//    }

//    int putProbeMatches(const wsd__ProbeMatchesType * a, const char * tag)
//    {
//        int id = soap_element_id(this, tag, -1, a, NULL, 0, NULL, SOAP_TYPE_wsd__ProbeMatchesType);
//        return (id < 0) ? error : a->soap_out(this, tag, id, NULL);
//    }


private:
    Wsa wsa_;
    Matches_t matches_;
};




//RemoteDiscovery::ResolveType Discovery::hello(Hello arg)
//{
//    static const std::string ACTION = SOAP_NAMESPACE_OF_wsdd"/Hello";

//    const auto messageId = impl_->genUuid();

//    // SOAP Header
//    const std::string & dst = TO_TS_URL;
//    soap_wsa_request(impl_, messageId.c_str(), dst.c_str(), ACTION.c_str());
//    soap_wsa_add_RelatesTo(impl_, "");

//    impl_->resetAppSequence();

//    // Hello
//    wsd__HelloType req;
//    soap_default_wsd__HelloType(impl_, &req);
//    req.wsa__EndpointReference.Address = const_cast<char *>(arg.endpoint.c_str());
//    req.Types = const_cast<char *>(arg.type.c_str());

//    wsd__ScopesType req_scopes;
//    if (!scopes.empty()) {
//        soap_default_wsd__ScopesType(impl_, &req_scopes);
//        req_scopes.__item = const_cast<char *>(scopes.c_str());
//        req_scopes.MatchBy = const_cast<char *>(matchBy.c_str());
//        req.Scopes = &req_scopes;
//    }
//    req.XAddrs = const_cast<char *>(xaddrs.c_str());
//    req.MetadataVersion = metadataVersion;

//    if (impl_->send_Hello(endpoint.c_str(), ACTION.c_str(), &req) != 0)
//        throw SoapException(impl_);

//    return RemoteDiscovery::ResolveType();
//}

//RemoteDiscovery::ResolveType Discovery::bye(ByeType)
//{
//    static const std::string ACTION = SOAP_NAMESPACE_OF_wsdd"/Bye";

//    // SOAP Header
//    const std::string & dst = mode == MODE_ADHOC ? endpoint : TO_TS_URL;
//    soap_wsa_request(impl_, messageId.c_str(), dst.c_str(), ACTION.c_str());
//#ifdef SOAP_WSA_2005
//    impl_->setAppSequence();
//#else
//    if (mode == MODE_ADHOC)
//        impl_->setAppSequence();
//    else
//        impl_->resetAppSequence();
//#endif

//    // Bye
//    wsd__ByeType req;
//    soap_default_wsd__ByeType(impl_, &req);
//#ifdef SOAP_WSA_2005
//    req.wsa5__EndpointReference.Address = const_cast<char *>(endpointRef.c_str());
//#else
//    req.wsa__EndpointReference.Address = const_cast<char *>(endpointRef.c_str());
//#endif
//    req.Types = const_cast<char *>(types.c_str());

//    wsd__ScopesType req_scopes;
//    if (!scopes.empty()) {
//        soap_default_wsd__ScopesType(impl_, &req_scopes);
//        req_scopes.__item = const_cast<char *>(scopes.c_str());
//        req_scopes.MatchBy = const_cast<char *>(matchBy.c_str());
//        req.Scopes = &req_scopes;
//    }
//    req.XAddrs = const_cast<char *>(xaddrs.c_str());
//    req.MetadataVersion = &metadataVersion;

//    if (impl_->send_Bye(endpoint.c_str(), ACTION.c_str(), &req) != 0)
//        throw SoapException(impl_);

//    return RemoteDiscovery::ResolveType();
//}


//void Discovery::resolve(ResolveType)
//{
//    static const std::string ACTION = SOAP_NAMESPACE_OF_wsdd"/Resolve";

//    // SOAP Header
//    const std::string & dst = to == TO_TS ? endpoint : TO_TS_URL;
//    soap_wsa_request(impl_, messageId.c_str(), dst.c_str(), ACTION.c_str());
//    soap_wsa_add_ReplyTo(impl_, replyTo.c_str());
//    impl_->resetAppSequence();

//    /* Probe */
//    wsd__ResolveType req;
//    soap_default_wsd__ResolveType(impl_, &req);
//#ifdef SOAP_WSA_2005
//    req.wsa5__EndpointReference.Address = const_cast<char *>(endpointRef.c_str());
//#else
//    req.wsa__EndpointReference.Address = const_cast<char *>(endpointRef.c_str());
//#endif

//    if (impl_->send_Resolve(endpoint.c_str(), ACTION.c_str(), &req) != 0)
//        throw SoapException(impl_);
//}

//void Discovery::probeMatches(const ProbeMatch::List_t & matches)
//{
//    static const std::string ACTION = SOAP_NAMESPACE_OF_wsdd"/ProbeMatches";

//    // 0..APP_MAX_DELAY ms delay
//    impl_->delay();

//    // SOAP Header
//    soap_wsa_request(impl_, messageId.c_str(), to.c_str(), ACTION.c_str());
//    soap_wsa_add_RelatesTo(impl_, relatesTo.c_str());
//    impl_->setAppSequence();

//    // ProbeMatches
//    ProbeMatches probe_matches(matches);
//    if (impl_->send_ProbeMatches(endpoint.c_str(), ACTION.c_str(), &probe_matches) != 0)
//        throw SoapException(impl_);


//}

//void Discovery::resolveMatches(const std::string & endpoint, const std::string & messageId,
//                          const std::string & relatesTo, const std::string & to,
//                          const std::string & endpointRef, const std::string & types,
//                          const std::string & scopes, const std::string & matchBy,
//                          const std::string & xaddrs, uint metadataVersion)
//{
//    static const std::string ACTION = SOAP_NAMESPACE_OF_wsdd"/ResolveMatches";

//    // 0..APP_MAX_DELAY ms delay
//    impl_->delay();

//    // SOAP Header
//    soap_wsa_request(impl_, messageId.c_str(), to.c_str(), ACTION.c_str());
//    soap_wsa_add_RelatesTo(impl_, relatesTo.c_str());
//    impl_->setAppSequence();

//    // ResolveMatches
//    wsd__ResolveMatchType match;
//    soap_default_wsd__ResolveMatchType(impl_, &match);
//#ifdef SOAP_WSA_2005
//    match.wsa5__EndpointReference.Address = const_cast<char *>(endpointRef.c_str());
//#else
//    match.wsa__EndpointReference.Address = const_cast<char *>(endpointRef.c_str());
//#endif
//    match.Types = const_cast<char *>(types.c_str());

//    wsd__ScopesType match_scopes;
//    if (!scopes.empty()) {
//      soap_default_wsd__ScopesType(impl_, &match_scopes);
//      match_scopes.__item = const_cast<char *>(scopes.c_str());
//      match_scopes.MatchBy = const_cast<char *>(matchBy.c_str());
//      match.Scopes = &match_scopes;
//    }
//    match.XAddrs = const_cast<char *>(xaddrs.c_str());
//    match.MetadataVersion = metadataVersion;


//    wsd__ResolveMatchesType res;
//    soap_default_wsd__ResolveMatchesType(impl_, &res);
//    res.ResolveMatch = &match;
//    if (impl_->send_ResolveMatches(endpoint.c_str(), ACTION.c_str(), &res) != 0)
//        throw SoapException(impl_);


//}


//Discovery::ProbeMatch::List_t Discovery::getProbeMatches()
//{
//    Discovery::ProbeMatch::List_t rv;

//    // managed mode: receive the matches
//    struct __wsd__ProbeMatches res;
//    wsd__ProbeMatchesType probe_matches;
//    soap_default_wsd__ProbeMatchesType(impl_, &probe_matches);
//    res.wsd__ProbeMatches = &probe_matches;

//    if (impl_->recv_ProbeMatches(res) != 0)
//        throw SoapException(impl_);

//    impl_->checkHeader("ProbeMatches wrong header");
//    if (res.wsd__ProbeMatches == NULL) {
//        if (soap_wsa_sender_fault(impl_, "WSDD ProbeMatches incomplete", NULL) == 0)
//            throw SoapException(impl_);
//    }

//    for (int i = 0; i < res.wsd__ProbeMatches->__sizeProbeMatch; ++i) {
//        auto & probe_match = res.wsd__ProbeMatches->ProbeMatch[i];
//        rv.push_back(ProbeMatch());

//        rv.back().endpoint.first    = Impl::toString(probe_match.wsa__EndpointReference.Address);
//        rv.back().types             = Impl::toString(probe_match.Types);
//        rv.back().scopes.item       = Impl::toString(probe_match.Scopes->__item);
//        rv.back().scopes.matchBy    = Impl::toString(probe_match.Scopes->MatchBy);
//        rv.back().xaddrs            = Impl::toString(probe_match.XAddrs);
//        rv.back().version           = probe_match.MetadataVersion;
//    }

//    return rv;
//}

//Discovery::ResolveMatch Discovery::getResolveMatch()
//{
//    ResolveMatch rv;

//    // managed mode: receive the matches
//    struct __wsd__ResolveMatches res;
//    soap_default_wsd__ResolveMatchesType(impl_, res.wsd__ResolveMatches);
//    if (impl_->recv_ResolveMatches(res) != 0)
//        throw SoapException(impl_);

//    impl_->checkHeader("WSDD ResolveMatches header incomplete");
//    if (res.wsd__ResolveMatches == NULL || res.wsd__ResolveMatches->ResolveMatch == NULL)
//        if (soap_wsa_sender_fault(impl_, "WSDD ResolveMatches incomplete", NULL) == 0)
//            throw SoapException(impl_);

//    auto resolve_match = res.wsd__ResolveMatches->ResolveMatch;
//    rv.endpoint.first = resolve_match->wsa__EndpointReference.Address;
//    rv.types = resolve_match->Types;
//    rv.scopes.item = resolve_match->Scopes->__item;
//    rv.scopes.matchBy = resolve_match->Scopes->MatchBy;
//    rv.xaddrs = resolve_match->XAddrs;
//    rv.version = resolve_match->MetadataVersion;

//    return rv;
//}

Service<RemoteDiscovery> * RemoteDiscovery::service()
{
    return new RemoteDiscoveryService();
}

//int Discovery::listen(int timeout)
//{
//    impl_->accept_timeout = impl_->recv_timeout = impl_->send_timeout = timeout;

//    // event-serve loop (exits upon timeout)
//    for (;;) {
//      if (!soap_valid_socket(soap_accept(impl_))) {
//        // timeout?
//        if (impl_->errnum == 0)
//          return impl_->error = SOAP_OK;

//        return impl_->error;
//      }

//      if (soap_begin_serve(impl_))
//        return impl_->error;

//      /* always close HTTP afterwards */
//      impl_->keep_alive = 0;

//      /* receive event and serve */
//      if (soap_wsdd_serve_request(impl_) != 0) {
//        // timeout?
//        if (!impl_->errnum)
//          return impl_->error = SOAP_OK;

//#ifdef WITH_FASTCGI
//        soap_send_fault(impl_);
//#else
//        return soap_send_fault(impl_);
//#endif
//      }

//      // clean up for next iteration
//      soap_destroy(impl_);
//      soap_end(impl_);
//    }
//}
