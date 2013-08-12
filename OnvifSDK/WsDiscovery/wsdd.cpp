
#include "wsdd.hpp"
#include "sigrlog.h"

Wsdd::Wsdd() :
    stopped_(false),
  bExitRequest_(false)
{
    SIGRLOG (SIGRDEBUG2, "start" );
    scopes_.push_back("onvif://www.onvif.org/type/NetworkVideoTransmitter");
    scopes_.push_back("onvif://www.onvif.org/type/video_encoder");
    scopes_.push_back("onvif://www.onvif.org/type/audio_encoder");
    scopes_.push_back("onvif://www.onvif.org/type/ptz");
    scopes_.push_back("onvif://www.onvif.org/name/OnvifxxExample");
    scopes_.push_back("onvif://www.onvif.org/location/Anywhere");
    scopes_.push_back("onvif://www.onvif.org/hardware/OnvifxxEngine");
}

Wsdd::~Wsdd()
{
}

int Wsdd::start(bool bIsDevice)
{
    bIsDevice_ = bIsDevice;
    mutex_ = PTHREAD_MUTEX_INITIALIZER;
    int iRet = pthread_create(&serviceThread_, NULL, &Wsdd::runServiceHelper, this);
    return iRet;
}

std::vector<std::string> Wsdd::getMembers()
{
    pthread_mutex_lock(&mutex_);
    std::vector<std::string> v = members_;
    pthread_mutex_unlock(&mutex_);
    return v;
}

int Wsdd::stop()
{
    pthread_mutex_lock(&mutex_);
    bExitRequest_ = true;
    pthread_mutex_unlock(&mutex_);
    pthread_join(serviceThread_, NULL);
    return 0;
}

void Wsdd::hello(const Hello_t & arg)
{
    SIGRLOG( SIGRDEBUG2,  "hello ( %s, %s, %s)",
              (arg.xaddrs != NULL ? arg.xaddrs->c_str() : ""),
              (arg.types != NULL ?  arg.types->c_str() : ""),
              (arg.scopes != NULL ? arg.scopes->item.c_str() : ""));
    if(arg.xaddrs != NULL && !arg.xaddrs->empty())
    {
        if (std::find(members_.begin(), members_.end(), *arg.xaddrs) == members_.end())
            members_.push_back(arg.xaddrs->c_str());
    }
}

void Wsdd::bye(const Bye_t & arg)
{
    SIGRLOG( SIGRDEBUG2,  "bye ( %s, %s, %s)",
              (arg.xaddrs != NULL ? arg.xaddrs->c_str() : ""),
              (arg.types != NULL ? arg.types->c_str() : ""),
              (arg.scopes != NULL ? arg.scopes->item.c_str() : ""));
}

Wsdd::ProbeMatches_t  Wsdd::probe(const Probe_t & arg)
{
    SIGRLOG( SIGRDEBUG2,  "probe ( %s, %s)",
             (arg.types != NULL ? arg.types->c_str() : ""),
             (arg.scopes != NULL ? arg.scopes->item.c_str() : ""));

    bool matched = true;
    if (arg.types != NULL && probeMatches_.back().types != NULL) {
        std::string types = *arg.types;
        while (true) {
            std::size_t pos1 = types.rfind(':');
            if (pos1 == std::string::npos)
                break;

            std::size_t pos2 = types.rfind(' ', pos1);
            if (pos2 == std::string::npos)
                pos2 = 0;
            else
                ++pos2;

            types.erase(pos2, pos1 - pos2 + 1);
        }

        matched = isMatched(types, *probeMatches_.back().types);
    }

    if (matched && arg.scopes != NULL && probeMatches_.back().scopes != NULL)
        matched = isMatched(arg.scopes->item, probeMatches_.back().scopes->item);

    return matched ? probeMatches_ : Wsdd::ProbeMatches_t();
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

bool Wsdd::isMatched(const std::string & left, const std::string & right)
{
    std::vector<std::string> l;
    std::vector<std::string> r;

    l = split(left, ' ');
    r = split(right, ' ');

    return std::find_first_of(l.begin(), l.end(), r.begin(), r.end()) != l.end();
}

template <class T>
std::string vector_join( const std::vector<T>& v, const std::string& token ){
  std::ostringstream result;
  for (typename std::vector<T>::const_iterator i = v.begin(); i != v.end(); i++){
    if (i != v.begin()) result << token;
    result << *i;
  }
  return result.str();
}

void Wsdd::runService()
{
    try {
        std::string address = "urn:uuid:05f1b46c-f29a-46f7-9140-e4bc00c8cea6";
        std::string xaddrs = "http://127.0.0.1/onvif/services";
        std::string types = "dn:NetworkVideoTransmitter";

        Scopes_t scopes = Scopes_t();
        scopes.item = vector_join(scopes_, " ");
        EndpointReference_t endpoint = EndpointReference_t();
        endpoint.address = &address;

        probeMatches_.resize(1);
        probeMatches_.back().endpoint = &endpoint;
        probeMatches_.back().scopes = &scopes;
        probeMatches_.back().types = &types;
        probeMatches_.back().xaddrs = &xaddrs;
        probeMatches_.back().version = 1;

        if(bIsDevice_)
        {
            SIGRLOG( SIGRDEBUG2,  "Sending hello" );
            proxy_.reset(RemoteDiscovery::proxy());
            proxy_->hello(probeMatches_.back());
        }


        SIGRLOG( SIGRDEBUG2,  "Starting the service loop" );
        std::tr1::shared_ptr<Service_t> service(RemoteDiscovery::service());
        service->bind(this);

        while (true) {

            pthread_mutex_lock(&mutex_);
            if(bExitRequest_)
            {
                service->destroy();
                bExitRequest_ = false;
                break;
            }
            pthread_mutex_unlock(&mutex_);


            SIGRLOG( SIGRDEBUG2,  "Accept" );
            if (service->accept() == -1) {
                SIGRLOG( SIGRWARNING,  "Accept failed" );
                continue;
            }

            SIGRLOG( SIGRDEBUG2,  "Serve" );
            int err = service->serve();
            if (err != 0) {
                if (err != -1) {
                    SIGRLOG( SIGRWARNING,  "Serve failed :%s", SoapException(service->getSoap()).what() );
                }
                continue;
            }

            SIGRLOG( SIGRDEBUG2,  "Clear");
            service->destroy();
        }

        if(bIsDevice_)
        {
            service.reset();
            proxy_.reset(RemoteDiscovery::proxy());
            proxy_->bye(probeMatches_.back());
        }

    } catch (std::exception & ex) {
        SIGRLOG( SIGRWARNING, "%s", ex.what() );

    }

    SIGRLOG( SIGRDEBUG0,  "The service loop stopped" );
}
