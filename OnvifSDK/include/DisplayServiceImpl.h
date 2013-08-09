#ifndef soapDisplayBindingServiceImpl_H
#define soapDisplayBindingServiceImpl_H

#include "soapDisplayBindingService.h"


class BaseServer;


class DisplayServiceImpl : public DisplayBindingService
{
private:
    BaseServer * m_pBaseServer;
public:
    DisplayServiceImpl(BaseServer * pBaseServer, struct soap* pData):DisplayBindingService(pData)
	{
        m_pBaseServer = pBaseServer;
	};

	virtual DisplayBindingService * copy();

	/// Web service operation 'GetServiceCapabilities' (returns error code or SOAP_OK)
	virtual	int GetServiceCapabilities(_tls__GetServiceCapabilities *tls__GetServiceCapabilities, _tls__GetServiceCapabilitiesResponse *tls__GetServiceCapabilitiesResponse) {return SOAP_OK;};

	/// Web service operation 'GetLayout' (returns error code or SOAP_OK)
	virtual	int GetLayout(_tls__GetLayout *tls__GetLayout, _tls__GetLayoutResponse *tls__GetLayoutResponse);

	/// Web service operation 'SetLayout' (returns error code or SOAP_OK)
    virtual	int SetLayout(_tls__SetLayout *tls__SetLayout, _tls__SetLayoutResponse *tls__SetLayoutResponse);

	/// Web service operation 'GetDisplayOptions' (returns error code or SOAP_OK)
	virtual	int GetDisplayOptions(_tls__GetDisplayOptions *tls__GetDisplayOptions, _tls__GetDisplayOptionsResponse *tls__GetDisplayOptionsResponse);

	/// Web service operation 'GetPaneConfigurations' (returns error code or SOAP_OK)
	virtual	int GetPaneConfigurations(_tls__GetPaneConfigurations *tls__GetPaneConfigurations, _tls__GetPaneConfigurationsResponse *tls__GetPaneConfigurationsResponse) {return SOAP_OK;};

	/// Web service operation 'GetPaneConfiguration' (returns error code or SOAP_OK)
	virtual	int GetPaneConfiguration(_tls__GetPaneConfiguration *tls__GetPaneConfiguration, _tls__GetPaneConfigurationResponse *tls__GetPaneConfigurationResponse) {return SOAP_OK;};

	/// Web service operation 'SetPaneConfigurations' (returns error code or SOAP_OK)
	virtual	int SetPaneConfigurations(_tls__SetPaneConfigurations *tls__SetPaneConfigurations, _tls__SetPaneConfigurationsResponse *tls__SetPaneConfigurationsResponse) {return SOAP_OK;};

	/// Web service operation 'SetPaneConfiguration' (returns error code or SOAP_OK)
	virtual	int SetPaneConfiguration(_tls__SetPaneConfiguration *tls__SetPaneConfiguration, _tls__SetPaneConfigurationResponse *tls__SetPaneConfigurationResponse) {return SOAP_OK;};

	/// Web service operation 'CreatePaneConfiguration' (returns error code or SOAP_OK)
    virtual	int CreatePaneConfiguration(_tls__CreatePaneConfiguration *tls__CreatePaneConfiguration, _tls__CreatePaneConfigurationResponse *tls__CreatePaneConfigurationResponse);

	/// Web service operation 'DeletePaneConfiguration' (returns error code or SOAP_OK)
	virtual	int DeletePaneConfiguration(_tls__DeletePaneConfiguration *tls__DeletePaneConfiguration, _tls__DeletePaneConfigurationResponse *tls__DeletePaneConfigurationResponse) {return SOAP_OK;};

};

#endif // soapDisplayBindingServiceImpl_H
