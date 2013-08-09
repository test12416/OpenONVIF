#ifndef soapReceiverBindingServiceImpl_H
#define soapReceiverBindingServiceImpl_H

#include "soapReceiverBindingService.h"


class BaseServer;


class ReceiverServiceImpl : public ReceiverBindingService
{
private:
    BaseServer * m_pBaseServer;
public:
    ReceiverServiceImpl(BaseServer * pBaseServer, struct soap * pData):ReceiverBindingService(pData)
	{
        m_pBaseServer = pBaseServer;
	};
	
	virtual	ReceiverBindingService *copy();

    /// Web service operation 'GetServiceCapabilities' (returns error code or SOAP_OK)
	virtual	int GetServiceCapabilities(_trv__GetServiceCapabilities *trv__GetServiceCapabilities, _trv__GetServiceCapabilitiesResponse *trv__GetServiceCapabilitiesResponse) {return SOAP_OK;};

	/// Web service operation 'GetReceivers' (returns error code or SOAP_OK)
	virtual	int GetReceivers(_trv__GetReceivers *trv__GetReceivers, _trv__GetReceiversResponse *trv__GetReceiversResponse);

	/// Web service operation 'GetReceiver' (returns error code or SOAP_OK)
	virtual	int GetReceiver(_trv__GetReceiver *trv__GetReceiver, _trv__GetReceiverResponse *trv__GetReceiverResponse) {return SOAP_OK;};

	/// Web service operation 'CreateReceiver' (returns error code or SOAP_OK)
    virtual	int CreateReceiver(_trv__CreateReceiver *trv__CreateReceiver, _trv__CreateReceiverResponse *trv__CreateReceiverResponse);

	/// Web service operation 'DeleteReceiver' (returns error code or SOAP_OK)
	virtual	int DeleteReceiver(_trv__DeleteReceiver *trv__DeleteReceiver, _trv__DeleteReceiverResponse *trv__DeleteReceiverResponse) {return SOAP_OK;};

	/// Web service operation 'ConfigureReceiver' (returns error code or SOAP_OK)
	virtual	int ConfigureReceiver(_trv__ConfigureReceiver *trv__ConfigureReceiver, _trv__ConfigureReceiverResponse *trv__ConfigureReceiverResponse) {return SOAP_OK;};

	/// Web service operation 'SetReceiverMode' (returns error code or SOAP_OK)
    virtual	int SetReceiverMode(_trv__SetReceiverMode *trv__SetReceiverMode, _trv__SetReceiverModeResponse *trv__SetReceiverModeResponse);

	/// Web service operation 'GetReceiverState' (returns error code or SOAP_OK)
	virtual	int GetReceiverState(_trv__GetReceiverState *trv__GetReceiverState, _trv__GetReceiverStateResponse *trv__GetReceiverStateResponse) {return SOAP_OK;};
};

#endif // soapReceiverBindingServiceImpl_H
