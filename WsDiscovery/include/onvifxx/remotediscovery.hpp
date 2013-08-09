#ifndef ONVIF_DISCOVERY_HPP
#define ONVIF_DISCOVERY_HPP

#include "onvifxx.hpp"

namespace onvifxx {

static const char WSDD_MULTICAT_IP[] = "239.255.255.250";
static const int WSDD_MULTICAT_PORT = 3702;

struct RemoteDiscovery
{
    typedef struct
    {
        std::string item;
        std::string * matchBy;
    } Scopes_t;

    typedef struct
    {
        std::string * address;
        std::string * portType;

        struct ServiceName
        {
            std::string item;
            std::string * portName;
        } * serviceName;
    } EndpointReference_t;

    typedef struct
    {
        std::string * types;
        Scopes_t * scopes;
    } Probe_t;

    typedef struct
    {
        EndpointReference_t * endpoint;
        std::string * types;
        Scopes_t * scopes;
        std::string * xaddrs;
        unsigned int version;
    } ProbeMatch_t;

    typedef ProbeMatch_t Hello_t;
    typedef ProbeMatch_t Bye_t;
    typedef std::vector<ProbeMatch_t> ProbeMatches_t;

    virtual void hello(const Hello_t & arg) = 0;
    virtual void bye(const Bye_t & arg) = 0;
    virtual ProbeMatches_t probe(const Probe_t & arg) = 0;
    //virtual void probeMatches(const ProbeMatches_t & arg, const std::string & relatesTo) = 0;

    static Proxy<RemoteDiscovery> * proxy();
    static Service<RemoteDiscovery> * service();
};

} // namespace onvifxx

#endif // ONVIF_DISCOVERY_HPP
