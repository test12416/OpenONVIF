#ifndef ONVIFXX_WSDD_HPP
#define ONVIFXX_WSDD_HPP

#if defined(SOAP_WSA_2003)
# define SOAP_WSA(member) wsa3__##member
# define SOAP_WSA_(prefix,member) prefix##_wsa3__##member
# define SOAP_WSA__(prefix,member) prefix##wsa3__##member
#elif defined(SOAP_WSA_2004)
# define SOAP_WSA(member) wsa4__##member
# define SOAP_WSA_(prefix,member) prefix##_wsa4__##member
# define SOAP_WSA__(prefix,member) prefix##wsa4__##member
#elif defined(SOAP_WSA_2005)
# define SOAP_WSA(member) wsa5__##member
# define SOAP_WSA_(prefix,member) prefix##_wsa5__##member
# define SOAP_WSA__(prefix,member) prefix##wsa5__##member
#else
# define SOAP_WSA(member) wsa__##member
# define SOAP_WSA_(prefix,member) prefix##_wsa__##member
# define SOAP_WSA__(prefix,member) prefix##wsa__##member
#endif

#include <onvifxx/onvifxx.hpp>
#include <WsddH.h>

class Wsa
{
public:
    Wsa(struct soap * soap);
    ~Wsa();

    static uint & instanceId();
    static std::string & sequenceId();
    static uint & messageNumber();

    std::string randUuid();

    int allocHeader();
    int check() const;

    int addFrom(const std::string & from);
    int addNoReply();
    int addReplyTo(const std::string & replyTo);
    int addFaultTo(const std::string & faultTo);
    int addRelatesTo(const std::string & relatesTo);
    int addAppSequence(std::string * id = nullptr);

    int reply(const std::string & id, const std::string & action);
    int request(const std::string & to, const std::string & action);


    template<class T>
    class Request : public T
    {
    public:
        template<class P>
        Request(struct soap * soap, const P & arg)
        {
            T::soap_default(soap);
            T::Types = arg.types;
            T::XAddrs = arg.xaddrs;

            if (arg.scopes != nullptr) {
                T::Scopes = &scopes_;
                T::Scopes->soap_default(soap);
                T::Scopes->__item = arg.scopes->item;
                T::Scopes->MatchBy = arg.scopes->matchBy;
            }

            if (arg.endpoint != nullptr) {
                T::wsa__EndpointReference = &endpoint_;
                T::wsa__EndpointReference->soap_default(soap);
                if (arg.endpoint->address != nullptr) {
                    T::wsa__EndpointReference->Address = &address_;
                    T::wsa__EndpointReference->Address->soap_default(soap);
                    T::wsa__EndpointReference->Address->__item = *arg.endpoint->address;
                }
                if (arg.endpoint->portType != nullptr) {
                    T::wsa__EndpointReference->PortType = &port_;
                    T::wsa__EndpointReference->PortType->soap_default(soap);
                    T::wsa__EndpointReference->PortType->__item = *arg.endpoint->portType;
                }

                if (arg.endpoint->serviceName != nullptr) {
                    T::wsa__EndpointReference->ServiceName = &service_;
                    T::wsa__EndpointReference->ServiceName->soap_default(soap);
                    T::wsa__EndpointReference->ServiceName->__item = arg.endpoint->serviceName->item;
                    T::wsa__EndpointReference->ServiceName->PortName = arg.endpoint->serviceName->portName;
                }
            }
        }

    private:
        wsd__ScopesType scopes_;
        wsa__EndpointReferenceType endpoint_;
        wsa__AttributedURI address_;
        wsa__AttributedQName port_;
        wsa__ServiceNameType service_;
    };

private:
    soap * soap_;
    wsd__AppSequenceType sequence_;
};

#endif // ONVIFXX_WSDD_HPP
