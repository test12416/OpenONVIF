#include <remotediscovery.hpp>
#include <WsddRemoteDiscoveryBindingProxy.h>
#include <Wsdd.nsmap>
#include "wsa.hpp"

#include <sstream>

const std::string TO_TS_URL = "urn:schemas-xmlsoap-org:ws:2005:04:discovery";

class RemoteDiscoveryProxy :
        public Proxy<RemoteDiscovery>,
        private RemoteDiscoveryBindingProxy
{
    static const uint SEND_TIMEOUT = 5; // second
    static const uint RECV_TIMEOUT = 5; // second

    static const uint APP_MAX_DELAY = 500;


public:
    RemoteDiscoveryProxy() :
        RemoteDiscoveryBindingProxy(url().c_str(), SOAP_IO_UDP),
        wsa_(RemoteDiscoveryBindingProxy::soap)
    {
        RemoteDiscoveryBindingProxy::soap->send_timeout = SEND_TIMEOUT;
        RemoteDiscoveryBindingProxy::soap->recv_timeout = RECV_TIMEOUT;
    }

    virtual ~RemoteDiscoveryProxy()
    {
        destroy();
        soap_done(RemoteDiscoveryBindingProxy::soap);
    }


    static std::string toString(const char * s)
    {
        return s == NULL ? std::string() : std::string(s);
    }


    void delay()
    {
        const unsigned int timeout = 1000 * (soap_random % APP_MAX_DELAY);
        ::usleep(timeout);
    }



    void checkHeader(const std::string & faultMessage)
    {
        // check WSA
        if (soap_header() == NULL) {
            if (soap_sender_fault(RemoteDiscoveryBindingProxy::soap, "checkHeader", faultMessage.c_str()) != 0)
                throw SoapException(RemoteDiscoveryBindingProxy::soap);
        }

//        if (soap_header()->wsd__AppSequence != NULL) {
//            wsd__AppSequenceType * seq = soap_header()->wsd__AppSequence;
//            instanceId() = seq->InstanceId;
//            messageNumber() = seq->MessageNumber;
//            if (seq->SequenceId != NULL)
//                sequenceId() = *seq->SequenceId;
//        }
    }

    virtual void hello(const Hello_t & arg)
    {
        // Header
        wsa_.request(TO_TS_URL, SOAP_NAMESPACE_OF_wsd"/Hello");
        wsa_.addAppSequence();

        // Body
        Wsa::Request<wsd__HelloType> req(RemoteDiscoveryBindingProxy::soap, arg);
        req.MetadataVersion = arg.version;
        if (Hello(&req, NULL) != 0)
            throw SoapException(RemoteDiscoveryBindingProxy::soap);
    }

    virtual void bye(const Bye_t & arg)
    {
        // Header
        wsa_.request(TO_TS_URL, SOAP_NAMESPACE_OF_wsd"/Bye");
        wsa_.addAppSequence();

        // Body
        Wsa::Request<wsd__ByeType> req(RemoteDiscoveryBindingProxy::soap, arg);
        req.Types = NULL;
        req.Scopes = NULL;
        req.XAddrs = NULL;
        //req.MetadataVersion = &arg.version;
        if (Bye(&req, NULL) != 0)
            throw SoapException(RemoteDiscoveryBindingProxy::soap);
    }

    virtual ProbeMatches_t probe(const Probe_t & arg)
    {
        // Header
        wsa_.request(TO_TS_URL, SOAP_NAMESPACE_OF_wsd"/Probe");

        // Body
        wsd__ProbeType req;
        req.soap_default(RemoteDiscoveryBindingProxy::soap);
        req.Types = arg.types;

        wsd__ScopesType req_scopes;
        req_scopes.soap_default(RemoteDiscoveryBindingProxy::soap);
        if (arg.scopes != NULL) {
            req_scopes.__item = arg.scopes->item;
            req_scopes.MatchBy = arg.scopes->matchBy;
            req.Scopes = &req_scopes;
        }

        if (Probe(&req, NULL) != 0)
            throw SoapException(RemoteDiscoveryBindingProxy::soap);
    }

//    virtual void probeMatches(const ProbeMatches_t & items, const std::string & relatesTo)
//    {
//        // Header
//        wsa_.request("", SOAP_NAMESPACE_OF_wsd"/ProbeMatches");
//        wsa_.addRelatesTo(relatesTo);

//        wsd__AppSequenceType app_sequence;
//        app_sequence.soap_default(this);
//        app_sequence.InstanceId = instanceId();
//        app_sequence.MessageNumber = messageNumber();
//        header->wsd__AppSequence = &app_sequence;

//        // Body
//        wsd__ProbeMatchesType req;
//        req.soap_default(this);

//        std::vector<TypeImpl<wsd__ProbeMatchType> > matches;
//        matches.reserve(items.size());
//        req.ProbeMatch.resize(items.size());
//        for (size_t i = 0, sz = items.size(); i < sz; ++i) {
//            matches.push_back(TypeImpl<wsd__ProbeMatchType>(this, items[i]));
//            matches.back().MetadataVersion = items[i].version;
//            req.ProbeMatch[i] = &matches.back();
//        }

//        encodingStyle = NULL;
//        soap_begin(this);
//        soap_serializeheader(this);
//        if (!soap_reference(this, &req, SOAP_TYPE_wsd__ProbeMatchesType))
//            req.soap_serialize(this);

//        if (soap_begin_count(this))
//            throw SoapException(this);

//        if (mode & SOAP_IO_LENGTH) {
//            if (soap_envelope_begin_out(this)
//             || soap_putheader(this)
//             || soap_body_begin_out(this)
//             || putProbeMatches(&req, "dn:ProbeMatches")
//             || soap_body_end_out(this)
//             || soap_envelope_end_out(this))
//                 throw SoapException(this);
//        }

//        if (soap_end_count(this))
//            throw SoapException(this);

//        if (soap_connect(this, soap_url(this, soap_endpoint, NULL), soap_header()->wsa__Action.c_str())
//         || soap_envelope_begin_out(this)
//         || soap_putheader(this)
//         || soap_body_begin_out(this)
//         || putProbeMatches(&req, "dn:ProbeMatches")
//         || soap_body_end_out(this)
//         || soap_envelope_end_out(this)
//         || soap_end_send(this)
//         || soap_closesock(this))
//            throw SoapException(this);
//    }

private:
    static std::string url()
    {
        std::stringstream ss;
        ss << "soap.udp://" << WSDD_MULTICAT_IP << ":" << WSDD_MULTICAT_PORT;
        return ss.str();
    }

private:
    Wsa wsa_;
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

Proxy<RemoteDiscovery> * RemoteDiscovery::proxy()
{
    return new RemoteDiscoveryProxy;
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
