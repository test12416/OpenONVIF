#ifndef WSDD_HPP
#define WSDD_HPP

#include <onvifxx/remotediscovery.hpp>

#include "WsddLib.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class Wsdd : public IWsdd,
        public onvifxx::RemoteDiscovery
{
    typedef onvifxx::Proxy<onvifxx::RemoteDiscovery> Proxy_t;
    typedef onvifxx::Service<onvifxx::RemoteDiscovery> Service_t;

public:
    virtual ~Wsdd();
    virtual int start(bool bIsDevice);
    virtual std::vector<std::string> getMembers();
    virtual int stop();

    static Wsdd* Instance()
    {
            static Wsdd theSingleInstance;
            return &theSingleInstance;
    }

private:
    Wsdd();
    Wsdd(const Wsdd& root);
    Wsdd& operator=(const Wsdd&);

    virtual void hello(const Hello_t & arg);
    virtual void bye(const Bye_t & arg);
    virtual ProbeMatches_t probe(const Probe_t & arg);

    static bool isMatched(const std::string & left, const std::string & right);

    void runService();
    static void * runServiceHelper(void * context)
    {
        ((Wsdd*)context)->runService();
    }

private:
    bool stopped_;
    bool bExitRequest_;
    bool bIsDevice_;

    pthread_mutex_t mutex_;
    pthread_t serviceThread_;

    std::vector<std::string> scopes_;
    ProbeMatches_t probeMatches_;
    std::shared_ptr<Proxy_t> proxy_;

    std::vector<std::string> members_;
};

#endif // WSDD_HPP
