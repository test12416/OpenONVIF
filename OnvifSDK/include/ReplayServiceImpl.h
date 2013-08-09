#ifndef ReplayServiceImpl_H
#define ReplayServiceImpl_H

#include "soapReplayBindingService.h"


class BaseServer;


class ReplayServiceImpl : public ReplayBindingService
{
private:
    BaseServer * m_pBaseServer;
public:
    ReplayServiceImpl(BaseServer * pBaseServer, struct soap * pData):
        m_pBaseServer(pBaseServer),
        ReplayBindingService(pData)
    {
    }

    virtual	ReplayBindingService *copy() { return NULL; }

    /// Web service operation 'GetServiceCapabilities' (returns error code or SOAP_OK)
    virtual	int GetServiceCapabilities(_trp__GetServiceCapabilities *trp__GetServiceCapabilities, _trp__GetServiceCapabilitiesResponse *trp__GetServiceCapabilitiesResponse) { return SOAP_OK; }

    /// Web service operation 'GetReplayUri' (returns error code or SOAP_OK)
    virtual	int GetReplayUri(_trp__GetReplayUri *trp__GetReplayUri, _trp__GetReplayUriResponse *trp__GetReplayUriResponse) { return SOAP_OK; }

    /// Web service operation 'GetReplayConfiguration' (returns error code or SOAP_OK)
    virtual	int GetReplayConfiguration(_trp__GetReplayConfiguration *trp__GetReplayConfiguration, _trp__GetReplayConfigurationResponse *trp__GetReplayConfigurationResponse) { return SOAP_OK; }

    /// Web service operation 'SetReplayConfiguration' (returns error code or SOAP_OK)
    virtual	int SetReplayConfiguration(_trp__SetReplayConfiguration *trp__SetReplayConfiguration, _trp__SetReplayConfigurationResponse *trp__SetReplayConfigurationResponse) { return SOAP_OK; }


};

#endif // ReplayServiceImpl
