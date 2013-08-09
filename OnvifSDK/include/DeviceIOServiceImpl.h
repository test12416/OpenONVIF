#ifndef soapDeviceIOBindingServiceImpl_H
#define soapDeviceIOBindingServiceImpl_H

#include "soapDeviceIOBindingService.h"

class BaseServer;


class DeviceIOServiceImpl : public DeviceIOBindingService
{
private:
    BaseServer * m_pBaseServer;
public:
    DeviceIOServiceImpl(BaseServer * pBaseServer, struct soap * pData):DeviceIOBindingService(pData)
	{
        m_pBaseServer = pBaseServer;
	};

	virtual DeviceIOBindingService* copy();

	/// Web service operation 'GetServiceCapabilities' (returns error code or SOAP_OK)
	virtual	int GetServiceCapabilities(_tmd__GetServiceCapabilities *tmd__GetServiceCapabilities, _tmd__GetServiceCapabilitiesResponse *tmd__GetServiceCapabilitiesResponse) {return SOAP_OK;};

	/// Web service operation 'GetRelayOutputOptions' (returns error code or SOAP_OK)
	virtual	int GetRelayOutputOptions(_tmd__GetRelayOutputOptions *tmd__GetRelayOutputOptions, _tmd__GetRelayOutputOptionsResponse *tmd__GetRelayOutputOptionsResponse) {return SOAP_OK;};

	/// Web service operation 'GetAudioSources' (returns error code or SOAP_OK)
	virtual	int GetAudioSources(_trt__GetAudioSources *trt__GetAudioSources, _trt__GetAudioSourcesResponse *trt__GetAudioSourcesResponse) {return SOAP_OK;};

	/// Web service operation 'GetAudioOutputs' (returns error code or SOAP_OK)
	virtual	int GetAudioOutputs(_trt__GetAudioOutputs *trt__GetAudioOutputs, _trt__GetAudioOutputsResponse *trt__GetAudioOutputsResponse) {return SOAP_OK;};

	/// Web service operation 'GetVideoSources' (returns error code or SOAP_OK)
	virtual	int GetVideoSources(_trt__GetVideoSources *trt__GetVideoSources, _trt__GetVideoSourcesResponse *trt__GetVideoSourcesResponse) {return SOAP_OK;};

	/// Web service operation 'GetVideoOutputs' (returns error code or SOAP_OK)
	virtual	int GetVideoOutputs(_tmd__GetVideoOutputs *tmd__GetVideoOutputs, _tmd__GetVideoOutputsResponse *tmd__GetVideoOutputsResponse);

	/// Web service operation 'GetVideoSourceConfiguration' (returns error code or SOAP_OK)
	virtual	int GetVideoSourceConfiguration(_tmd__GetVideoSourceConfiguration *tmd__GetVideoSourceConfiguration, _tmd__GetVideoSourceConfigurationResponse *tmd__GetVideoSourceConfigurationResponse) {return SOAP_OK;};

	/// Web service operation 'GetVideoOutputConfiguration' (returns error code or SOAP_OK)
	virtual	int GetVideoOutputConfiguration(_tmd__GetVideoOutputConfiguration *tmd__GetVideoOutputConfiguration, _tmd__GetVideoOutputConfigurationResponse *tmd__GetVideoOutputConfigurationResponse) {return SOAP_OK;};

	/// Web service operation 'GetAudioSourceConfiguration' (returns error code or SOAP_OK)
	virtual	int GetAudioSourceConfiguration(_tmd__GetAudioSourceConfiguration *tmd__GetAudioSourceConfiguration, _tmd__GetAudioSourceConfigurationResponse *tmd__GetAudioSourceConfigurationResponse) {return SOAP_OK;};

	/// Web service operation 'GetAudioOutputConfiguration' (returns error code or SOAP_OK)
	virtual	int GetAudioOutputConfiguration(_tmd__GetAudioOutputConfiguration *tmd__GetAudioOutputConfiguration, _tmd__GetAudioOutputConfigurationResponse *tmd__GetAudioOutputConfigurationResponse) {return SOAP_OK;};

	/// Web service operation 'SetVideoSourceConfiguration' (returns error code or SOAP_OK)
	virtual	int SetVideoSourceConfiguration(_tmd__SetVideoSourceConfiguration *tmd__SetVideoSourceConfiguration, _tmd__SetVideoSourceConfigurationResponse *tmd__SetVideoSourceConfigurationResponse) {return SOAP_OK;};

	/// Web service operation 'SetVideoOutputConfiguration' (returns error code or SOAP_OK)
	virtual	int SetVideoOutputConfiguration(_tmd__SetVideoOutputConfiguration *tmd__SetVideoOutputConfiguration, _tmd__SetVideoOutputConfigurationResponse *tmd__SetVideoOutputConfigurationResponse) {return SOAP_OK;};

	/// Web service operation 'SetAudioSourceConfiguration' (returns error code or SOAP_OK)
	virtual	int SetAudioSourceConfiguration(_tmd__SetAudioSourceConfiguration *tmd__SetAudioSourceConfiguration, _tmd__SetAudioSourceConfigurationResponse *tmd__SetAudioSourceConfigurationResponse) {return SOAP_OK;};

	/// Web service operation 'SetAudioOutputConfiguration' (returns error code or SOAP_OK)
	virtual	int SetAudioOutputConfiguration(_tmd__SetAudioOutputConfiguration *tmd__SetAudioOutputConfiguration, _tmd__SetAudioOutputConfigurationResponse *tmd__SetAudioOutputConfigurationResponse) {return SOAP_OK;};

	/// Web service operation 'GetVideoSourceConfigurationOptions' (returns error code or SOAP_OK)
	virtual	int GetVideoSourceConfigurationOptions(_tmd__GetVideoSourceConfigurationOptions *tmd__GetVideoSourceConfigurationOptions, _tmd__GetVideoSourceConfigurationOptionsResponse *tmd__GetVideoSourceConfigurationOptionsResponse) {return SOAP_OK;};

	/// Web service operation 'GetVideoOutputConfigurationOptions' (returns error code or SOAP_OK)
	virtual	int GetVideoOutputConfigurationOptions(_tmd__GetVideoOutputConfigurationOptions *tmd__GetVideoOutputConfigurationOptions, _tmd__GetVideoOutputConfigurationOptionsResponse *tmd__GetVideoOutputConfigurationOptionsResponse) {return SOAP_OK;};

	/// Web service operation 'GetAudioSourceConfigurationOptions' (returns error code or SOAP_OK)
	virtual	int GetAudioSourceConfigurationOptions(_tmd__GetAudioSourceConfigurationOptions *tmd__GetAudioSourceConfigurationOptions, _tmd__GetAudioSourceConfigurationOptionsResponse *tmd__GetAudioSourceConfigurationOptionsResponse) {return SOAP_OK;};

	/// Web service operation 'GetAudioOutputConfigurationOptions' (returns error code or SOAP_OK)
	virtual	int GetAudioOutputConfigurationOptions(_tmd__GetAudioOutputConfigurationOptions *tmd__GetAudioOutputConfigurationOptions, _tmd__GetAudioOutputConfigurationOptionsResponse *tmd__GetAudioOutputConfigurationOptionsResponse) {return SOAP_OK;};

	/// Web service operation 'GetRelayOutputs' (returns error code or SOAP_OK)
	virtual	int GetRelayOutputs(_tds__GetRelayOutputs *tds__GetRelayOutputs, _tds__GetRelayOutputsResponse *tds__GetRelayOutputsResponse) {return SOAP_OK;};

	/// Web service operation 'SetRelayOutputSettings' (returns error code or SOAP_OK)
	virtual	int SetRelayOutputSettings(_tmd__SetRelayOutputSettings *tmd__SetRelayOutputSettings, _tmd__SetRelayOutputSettingsResponse *tmd__SetRelayOutputSettingsResponse) {return SOAP_OK;};

	/// Web service operation 'SetRelayOutputState' (returns error code or SOAP_OK)
	virtual	int SetRelayOutputState(_tds__SetRelayOutputState *tds__SetRelayOutputState, _tds__SetRelayOutputStateResponse *tds__SetRelayOutputStateResponse) {return SOAP_OK;};

	/// Web service operation 'GetDigitalInputs' (returns error code or SOAP_OK)
	virtual	int GetDigitalInputs(_tmd__GetDigitalInputs *tmd__GetDigitalInputs, _tmd__GetDigitalInputsResponse *tmd__GetDigitalInputsResponse) {return SOAP_OK;};

	/// Web service operation 'GetSerialPorts' (returns error code or SOAP_OK)
	virtual	int GetSerialPorts(_tmd__GetSerialPorts *tmd__GetSerialPorts, _tmd__GetSerialPortsResponse *tmd__GetSerialPortsResponse) {return SOAP_OK;};

	/// Web service operation 'GetSerialPortConfiguration' (returns error code or SOAP_OK)
	virtual	int GetSerialPortConfiguration(_tmd__GetSerialPortConfiguration *tmd__GetSerialPortConfiguration, _tmd__GetSerialPortConfigurationResponse *tmd__GetSerialPortConfigurationResponse) {return SOAP_OK;};

	/// Web service operation 'SetSerialPortConfiguration' (returns error code or SOAP_OK)
	virtual	int SetSerialPortConfiguration(_tmd__SetSerialPortConfiguration *tmd__SetSerialPortConfiguration, _tmd__SetSerialPortConfigurationResponse *tmd__SetSerialPortConfigurationResponse) {return SOAP_OK;};

	/// Web service operation 'GetSerialPortConfigurationOptions' (returns error code or SOAP_OK)
	virtual	int GetSerialPortConfigurationOptions(_tmd__GetSerialPortConfigurationOptions *tmd__GetSerialPortConfigurationOptions, _tmd__GetSerialPortConfigurationOptionsResponse *tmd__GetSerialPortConfigurationOptionsResponse) {return SOAP_OK;};

	/// Web service operation 'SendReceiveSerialCommand' (returns error code or SOAP_OK)
	virtual	int SendReceiveSerialCommand(_tmd__SendReceiveSerialCommand *tmd__SendReceiveSerialCommand, _tmd__SendReceiveSerialCommandResponse *tmd__SendReceiveSerialCommandResponse) {return SOAP_OK;};
};
#endif // soapDeviceIOBindingServiceImpl_H
