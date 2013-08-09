#ifndef soapMediaBindingServiceImpl_H
#define soapMediaBindingServiceImpl_H

#include "stdafx.h"
#include "soapMediaBindingService.h"


class OnvifServer;


class MediaServiceImpl : public MediaBindingService
{
private:
	OnvifServer * m_pOnvifServer;
public:
	MediaServiceImpl(OnvifServer * pOnvifServer):MediaBindingService()
	{
		m_pOnvifServer = pOnvifServer;
	}

	/// Web service operation 'GetServiceCapabilities' (returns error code or SOAP_OK)
	virtual	int GetServiceCapabilities(_ns8__GetServiceCapabilities *ns8__GetServiceCapabilities, _ns8__GetServiceCapabilitiesResponse *ns8__GetServiceCapabilitiesResponse){return SOAP_OK;};

	/// Web service operation 'GetVideoSources' (returns error code or SOAP_OK)
	virtual	int GetVideoSources(_ns8__GetVideoSources *ns8__GetVideoSources, _ns8__GetVideoSourcesResponse *ns8__GetVideoSourcesResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioSources' (returns error code or SOAP_OK)
	virtual	int GetAudioSources(_ns8__GetAudioSources *ns8__GetAudioSources, _ns8__GetAudioSourcesResponse *ns8__GetAudioSourcesResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioOutputs' (returns error code or SOAP_OK)
	virtual	int GetAudioOutputs(_ns8__GetAudioOutputs *ns8__GetAudioOutputs, _ns8__GetAudioOutputsResponse *ns8__GetAudioOutputsResponse){return SOAP_OK;};

	/// Web service operation 'CreateProfile' (returns error code or SOAP_OK)
	virtual	int CreateProfile(_ns8__CreateProfile *ns8__CreateProfile, _ns8__CreateProfileResponse *ns8__CreateProfileResponse){return SOAP_OK;};

	/// Web service operation 'GetProfile' (returns error code or SOAP_OK)
	virtual	int GetProfile(_ns8__GetProfile *ns8__GetProfile, _ns8__GetProfileResponse *ns8__GetProfileResponse){return SOAP_OK;};

	/// Web service operation 'GetProfiles' (returns error code or SOAP_OK)
	virtual	int GetProfiles(_ns8__GetProfiles *ns8__GetProfiles, _ns8__GetProfilesResponse *ns8__GetProfilesResponse){return SOAP_OK;};

	/// Web service operation 'AddVideoEncoderConfiguration' (returns error code or SOAP_OK)
	virtual	int AddVideoEncoderConfiguration(_ns8__AddVideoEncoderConfiguration *ns8__AddVideoEncoderConfiguration, _ns8__AddVideoEncoderConfigurationResponse *ns8__AddVideoEncoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'AddVideoSourceConfiguration' (returns error code or SOAP_OK)
	virtual	int AddVideoSourceConfiguration(_ns8__AddVideoSourceConfiguration *ns8__AddVideoSourceConfiguration, _ns8__AddVideoSourceConfigurationResponse *ns8__AddVideoSourceConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'AddAudioEncoderConfiguration' (returns error code or SOAP_OK)
	virtual	int AddAudioEncoderConfiguration(_ns8__AddAudioEncoderConfiguration *ns8__AddAudioEncoderConfiguration, _ns8__AddAudioEncoderConfigurationResponse *ns8__AddAudioEncoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'AddAudioSourceConfiguration' (returns error code or SOAP_OK)
	virtual	int AddAudioSourceConfiguration(_ns8__AddAudioSourceConfiguration *ns8__AddAudioSourceConfiguration, _ns8__AddAudioSourceConfigurationResponse *ns8__AddAudioSourceConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'AddPTZConfiguration' (returns error code or SOAP_OK)
	virtual	int AddPTZConfiguration(_ns8__AddPTZConfiguration *ns8__AddPTZConfiguration, _ns8__AddPTZConfigurationResponse *ns8__AddPTZConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'AddVideoAnalyticsConfiguration' (returns error code or SOAP_OK)
	virtual	int AddVideoAnalyticsConfiguration(_ns8__AddVideoAnalyticsConfiguration *ns8__AddVideoAnalyticsConfiguration, _ns8__AddVideoAnalyticsConfigurationResponse *ns8__AddVideoAnalyticsConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'AddMetadataConfiguration' (returns error code or SOAP_OK)
	virtual	int AddMetadataConfiguration(_ns8__AddMetadataConfiguration *ns8__AddMetadataConfiguration, _ns8__AddMetadataConfigurationResponse *ns8__AddMetadataConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'AddAudioOutputConfiguration' (returns error code or SOAP_OK)
	virtual	int AddAudioOutputConfiguration(_ns8__AddAudioOutputConfiguration *ns8__AddAudioOutputConfiguration, _ns8__AddAudioOutputConfigurationResponse *ns8__AddAudioOutputConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'AddAudioDecoderConfiguration' (returns error code or SOAP_OK)
	virtual	int AddAudioDecoderConfiguration(_ns8__AddAudioDecoderConfiguration *ns8__AddAudioDecoderConfiguration, _ns8__AddAudioDecoderConfigurationResponse *ns8__AddAudioDecoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'RemoveVideoEncoderConfiguration' (returns error code or SOAP_OK)
	virtual	int RemoveVideoEncoderConfiguration(_ns8__RemoveVideoEncoderConfiguration *ns8__RemoveVideoEncoderConfiguration, _ns8__RemoveVideoEncoderConfigurationResponse *ns8__RemoveVideoEncoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'RemoveVideoSourceConfiguration' (returns error code or SOAP_OK)
	virtual	int RemoveVideoSourceConfiguration(_ns8__RemoveVideoSourceConfiguration *ns8__RemoveVideoSourceConfiguration, _ns8__RemoveVideoSourceConfigurationResponse *ns8__RemoveVideoSourceConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'RemoveAudioEncoderConfiguration' (returns error code or SOAP_OK)
	virtual	int RemoveAudioEncoderConfiguration(_ns8__RemoveAudioEncoderConfiguration *ns8__RemoveAudioEncoderConfiguration, _ns8__RemoveAudioEncoderConfigurationResponse *ns8__RemoveAudioEncoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'RemoveAudioSourceConfiguration' (returns error code or SOAP_OK)
	virtual	int RemoveAudioSourceConfiguration(_ns8__RemoveAudioSourceConfiguration *ns8__RemoveAudioSourceConfiguration, _ns8__RemoveAudioSourceConfigurationResponse *ns8__RemoveAudioSourceConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'RemovePTZConfiguration' (returns error code or SOAP_OK)
	virtual	int RemovePTZConfiguration(_ns8__RemovePTZConfiguration *ns8__RemovePTZConfiguration, _ns8__RemovePTZConfigurationResponse *ns8__RemovePTZConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'RemoveVideoAnalyticsConfiguration' (returns error code or SOAP_OK)
	virtual	int RemoveVideoAnalyticsConfiguration(_ns8__RemoveVideoAnalyticsConfiguration *ns8__RemoveVideoAnalyticsConfiguration, _ns8__RemoveVideoAnalyticsConfigurationResponse *ns8__RemoveVideoAnalyticsConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'RemoveMetadataConfiguration' (returns error code or SOAP_OK)
	virtual	int RemoveMetadataConfiguration(_ns8__RemoveMetadataConfiguration *ns8__RemoveMetadataConfiguration, _ns8__RemoveMetadataConfigurationResponse *ns8__RemoveMetadataConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'RemoveAudioOutputConfiguration' (returns error code or SOAP_OK)
	virtual	int RemoveAudioOutputConfiguration(_ns8__RemoveAudioOutputConfiguration *ns8__RemoveAudioOutputConfiguration, _ns8__RemoveAudioOutputConfigurationResponse *ns8__RemoveAudioOutputConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'RemoveAudioDecoderConfiguration' (returns error code or SOAP_OK)
	virtual	int RemoveAudioDecoderConfiguration(_ns8__RemoveAudioDecoderConfiguration *ns8__RemoveAudioDecoderConfiguration, _ns8__RemoveAudioDecoderConfigurationResponse *ns8__RemoveAudioDecoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'DeleteProfile' (returns error code or SOAP_OK)
	virtual	int DeleteProfile(_ns8__DeleteProfile *ns8__DeleteProfile, _ns8__DeleteProfileResponse *ns8__DeleteProfileResponse){return SOAP_OK;};

	/// Web service operation 'GetVideoSourceConfigurations' (returns error code or SOAP_OK)
	virtual	int GetVideoSourceConfigurations(_ns8__GetVideoSourceConfigurations *ns8__GetVideoSourceConfigurations, _ns8__GetVideoSourceConfigurationsResponse *ns8__GetVideoSourceConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetVideoEncoderConfigurations' (returns error code or SOAP_OK)
	virtual	int GetVideoEncoderConfigurations(_ns8__GetVideoEncoderConfigurations *ns8__GetVideoEncoderConfigurations, _ns8__GetVideoEncoderConfigurationsResponse *ns8__GetVideoEncoderConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioSourceConfigurations' (returns error code or SOAP_OK)
	virtual	int GetAudioSourceConfigurations(_ns8__GetAudioSourceConfigurations *ns8__GetAudioSourceConfigurations, _ns8__GetAudioSourceConfigurationsResponse *ns8__GetAudioSourceConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioEncoderConfigurations' (returns error code or SOAP_OK)
	virtual	int GetAudioEncoderConfigurations(_ns8__GetAudioEncoderConfigurations *ns8__GetAudioEncoderConfigurations, _ns8__GetAudioEncoderConfigurationsResponse *ns8__GetAudioEncoderConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetVideoAnalyticsConfigurations' (returns error code or SOAP_OK)
	virtual	int GetVideoAnalyticsConfigurations(_ns8__GetVideoAnalyticsConfigurations *ns8__GetVideoAnalyticsConfigurations, _ns8__GetVideoAnalyticsConfigurationsResponse *ns8__GetVideoAnalyticsConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetMetadataConfigurations' (returns error code or SOAP_OK)
	virtual	int GetMetadataConfigurations(_ns8__GetMetadataConfigurations *ns8__GetMetadataConfigurations, _ns8__GetMetadataConfigurationsResponse *ns8__GetMetadataConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioOutputConfigurations' (returns error code or SOAP_OK)
	virtual	int GetAudioOutputConfigurations(_ns8__GetAudioOutputConfigurations *ns8__GetAudioOutputConfigurations, _ns8__GetAudioOutputConfigurationsResponse *ns8__GetAudioOutputConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioDecoderConfigurations' (returns error code or SOAP_OK)
	virtual	int GetAudioDecoderConfigurations(_ns8__GetAudioDecoderConfigurations *ns8__GetAudioDecoderConfigurations, _ns8__GetAudioDecoderConfigurationsResponse *ns8__GetAudioDecoderConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetVideoSourceConfiguration' (returns error code or SOAP_OK)
	virtual	int GetVideoSourceConfiguration(_ns8__GetVideoSourceConfiguration *ns8__GetVideoSourceConfiguration, _ns8__GetVideoSourceConfigurationResponse *ns8__GetVideoSourceConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'GetVideoEncoderConfiguration' (returns error code or SOAP_OK)
	virtual	int GetVideoEncoderConfiguration(_ns8__GetVideoEncoderConfiguration *ns8__GetVideoEncoderConfiguration, _ns8__GetVideoEncoderConfigurationResponse *ns8__GetVideoEncoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioSourceConfiguration' (returns error code or SOAP_OK)
	virtual	int GetAudioSourceConfiguration(_ns8__GetAudioSourceConfiguration *ns8__GetAudioSourceConfiguration, _ns8__GetAudioSourceConfigurationResponse *ns8__GetAudioSourceConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioEncoderConfiguration' (returns error code or SOAP_OK)
	virtual	int GetAudioEncoderConfiguration(_ns8__GetAudioEncoderConfiguration *ns8__GetAudioEncoderConfiguration, _ns8__GetAudioEncoderConfigurationResponse *ns8__GetAudioEncoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'GetVideoAnalyticsConfiguration' (returns error code or SOAP_OK)
	virtual	int GetVideoAnalyticsConfiguration(_ns8__GetVideoAnalyticsConfiguration *ns8__GetVideoAnalyticsConfiguration, _ns8__GetVideoAnalyticsConfigurationResponse *ns8__GetVideoAnalyticsConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'GetMetadataConfiguration' (returns error code or SOAP_OK)
	virtual	int GetMetadataConfiguration(_ns8__GetMetadataConfiguration *ns8__GetMetadataConfiguration, _ns8__GetMetadataConfigurationResponse *ns8__GetMetadataConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioOutputConfiguration' (returns error code or SOAP_OK)
	virtual	int GetAudioOutputConfiguration(_ns8__GetAudioOutputConfiguration *ns8__GetAudioOutputConfiguration, _ns8__GetAudioOutputConfigurationResponse *ns8__GetAudioOutputConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioDecoderConfiguration' (returns error code or SOAP_OK)
	virtual	int GetAudioDecoderConfiguration(_ns8__GetAudioDecoderConfiguration *ns8__GetAudioDecoderConfiguration, _ns8__GetAudioDecoderConfigurationResponse *ns8__GetAudioDecoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'GetCompatibleVideoEncoderConfigurations' (returns error code or SOAP_OK)
	virtual	int GetCompatibleVideoEncoderConfigurations(_ns8__GetCompatibleVideoEncoderConfigurations *ns8__GetCompatibleVideoEncoderConfigurations, _ns8__GetCompatibleVideoEncoderConfigurationsResponse *ns8__GetCompatibleVideoEncoderConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetCompatibleVideoSourceConfigurations' (returns error code or SOAP_OK)
	virtual	int GetCompatibleVideoSourceConfigurations(_ns8__GetCompatibleVideoSourceConfigurations *ns8__GetCompatibleVideoSourceConfigurations, _ns8__GetCompatibleVideoSourceConfigurationsResponse *ns8__GetCompatibleVideoSourceConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetCompatibleAudioEncoderConfigurations' (returns error code or SOAP_OK)
	virtual	int GetCompatibleAudioEncoderConfigurations(_ns8__GetCompatibleAudioEncoderConfigurations *ns8__GetCompatibleAudioEncoderConfigurations, _ns8__GetCompatibleAudioEncoderConfigurationsResponse *ns8__GetCompatibleAudioEncoderConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetCompatibleAudioSourceConfigurations' (returns error code or SOAP_OK)
	virtual	int GetCompatibleAudioSourceConfigurations(_ns8__GetCompatibleAudioSourceConfigurations *ns8__GetCompatibleAudioSourceConfigurations, _ns8__GetCompatibleAudioSourceConfigurationsResponse *ns8__GetCompatibleAudioSourceConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetCompatibleVideoAnalyticsConfigurations' (returns error code or SOAP_OK)
	virtual	int GetCompatibleVideoAnalyticsConfigurations(_ns8__GetCompatibleVideoAnalyticsConfigurations *ns8__GetCompatibleVideoAnalyticsConfigurations, _ns8__GetCompatibleVideoAnalyticsConfigurationsResponse *ns8__GetCompatibleVideoAnalyticsConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetCompatibleMetadataConfigurations' (returns error code or SOAP_OK)
	virtual	int GetCompatibleMetadataConfigurations(_ns8__GetCompatibleMetadataConfigurations *ns8__GetCompatibleMetadataConfigurations, _ns8__GetCompatibleMetadataConfigurationsResponse *ns8__GetCompatibleMetadataConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetCompatibleAudioOutputConfigurations' (returns error code or SOAP_OK)
	virtual	int GetCompatibleAudioOutputConfigurations(_ns8__GetCompatibleAudioOutputConfigurations *ns8__GetCompatibleAudioOutputConfigurations, _ns8__GetCompatibleAudioOutputConfigurationsResponse *ns8__GetCompatibleAudioOutputConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetCompatibleAudioDecoderConfigurations' (returns error code or SOAP_OK)
	virtual	int GetCompatibleAudioDecoderConfigurations(_ns8__GetCompatibleAudioDecoderConfigurations *ns8__GetCompatibleAudioDecoderConfigurations, _ns8__GetCompatibleAudioDecoderConfigurationsResponse *ns8__GetCompatibleAudioDecoderConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'SetVideoSourceConfiguration' (returns error code or SOAP_OK)
	virtual	int SetVideoSourceConfiguration(_ns8__SetVideoSourceConfiguration *ns8__SetVideoSourceConfiguration, _ns8__SetVideoSourceConfigurationResponse *ns8__SetVideoSourceConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'SetVideoEncoderConfiguration' (returns error code or SOAP_OK)
	virtual	int SetVideoEncoderConfiguration(_ns8__SetVideoEncoderConfiguration *ns8__SetVideoEncoderConfiguration, _ns8__SetVideoEncoderConfigurationResponse *ns8__SetVideoEncoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'SetAudioSourceConfiguration' (returns error code or SOAP_OK)
	virtual	int SetAudioSourceConfiguration(_ns8__SetAudioSourceConfiguration *ns8__SetAudioSourceConfiguration, _ns8__SetAudioSourceConfigurationResponse *ns8__SetAudioSourceConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'SetAudioEncoderConfiguration' (returns error code or SOAP_OK)
	virtual	int SetAudioEncoderConfiguration(_ns8__SetAudioEncoderConfiguration *ns8__SetAudioEncoderConfiguration, _ns8__SetAudioEncoderConfigurationResponse *ns8__SetAudioEncoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'SetVideoAnalyticsConfiguration' (returns error code or SOAP_OK)
	virtual	int SetVideoAnalyticsConfiguration(_ns8__SetVideoAnalyticsConfiguration *ns8__SetVideoAnalyticsConfiguration, _ns8__SetVideoAnalyticsConfigurationResponse *ns8__SetVideoAnalyticsConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'SetMetadataConfiguration' (returns error code or SOAP_OK)
	virtual	int SetMetadataConfiguration(_ns8__SetMetadataConfiguration *ns8__SetMetadataConfiguration, _ns8__SetMetadataConfigurationResponse *ns8__SetMetadataConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'SetAudioOutputConfiguration' (returns error code or SOAP_OK)
	virtual	int SetAudioOutputConfiguration(_ns8__SetAudioOutputConfiguration *ns8__SetAudioOutputConfiguration, _ns8__SetAudioOutputConfigurationResponse *ns8__SetAudioOutputConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'SetAudioDecoderConfiguration' (returns error code or SOAP_OK)
	virtual	int SetAudioDecoderConfiguration(_ns8__SetAudioDecoderConfiguration *ns8__SetAudioDecoderConfiguration, _ns8__SetAudioDecoderConfigurationResponse *ns8__SetAudioDecoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'GetVideoSourceConfigurationOptions' (returns error code or SOAP_OK)
	virtual	int GetVideoSourceConfigurationOptions(_ns8__GetVideoSourceConfigurationOptions *ns8__GetVideoSourceConfigurationOptions, _ns8__GetVideoSourceConfigurationOptionsResponse *ns8__GetVideoSourceConfigurationOptionsResponse){return SOAP_OK;};

	/// Web service operation 'GetVideoEncoderConfigurationOptions' (returns error code or SOAP_OK)
	virtual	int GetVideoEncoderConfigurationOptions(_ns8__GetVideoEncoderConfigurationOptions *ns8__GetVideoEncoderConfigurationOptions, _ns8__GetVideoEncoderConfigurationOptionsResponse *ns8__GetVideoEncoderConfigurationOptionsResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioSourceConfigurationOptions' (returns error code or SOAP_OK)
	virtual	int GetAudioSourceConfigurationOptions(_ns8__GetAudioSourceConfigurationOptions *ns8__GetAudioSourceConfigurationOptions, _ns8__GetAudioSourceConfigurationOptionsResponse *ns8__GetAudioSourceConfigurationOptionsResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioEncoderConfigurationOptions' (returns error code or SOAP_OK)
	virtual	int GetAudioEncoderConfigurationOptions(_ns8__GetAudioEncoderConfigurationOptions *ns8__GetAudioEncoderConfigurationOptions, _ns8__GetAudioEncoderConfigurationOptionsResponse *ns8__GetAudioEncoderConfigurationOptionsResponse){return SOAP_OK;};

	/// Web service operation 'GetMetadataConfigurationOptions' (returns error code or SOAP_OK)
	virtual	int GetMetadataConfigurationOptions(_ns8__GetMetadataConfigurationOptions *ns8__GetMetadataConfigurationOptions, _ns8__GetMetadataConfigurationOptionsResponse *ns8__GetMetadataConfigurationOptionsResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioOutputConfigurationOptions' (returns error code or SOAP_OK)
	virtual	int GetAudioOutputConfigurationOptions(_ns8__GetAudioOutputConfigurationOptions *ns8__GetAudioOutputConfigurationOptions, _ns8__GetAudioOutputConfigurationOptionsResponse *ns8__GetAudioOutputConfigurationOptionsResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioDecoderConfigurationOptions' (returns error code or SOAP_OK)
	virtual	int GetAudioDecoderConfigurationOptions(_ns8__GetAudioDecoderConfigurationOptions *ns8__GetAudioDecoderConfigurationOptions, _ns8__GetAudioDecoderConfigurationOptionsResponse *ns8__GetAudioDecoderConfigurationOptionsResponse){return SOAP_OK;};

	/// Web service operation 'GetGuaranteedNumberOfVideoEncoderInstances' (returns error code or SOAP_OK)
	virtual	int GetGuaranteedNumberOfVideoEncoderInstances(_ns8__GetGuaranteedNumberOfVideoEncoderInstances *ns8__GetGuaranteedNumberOfVideoEncoderInstances, _ns8__GetGuaranteedNumberOfVideoEncoderInstancesResponse *ns8__GetGuaranteedNumberOfVideoEncoderInstancesResponse){return SOAP_OK;};

	/// Web service operation 'GetStreamUri' (returns error code or SOAP_OK)
	virtual	int GetStreamUri(_ns8__GetStreamUri *ns8__GetStreamUri, _ns8__GetStreamUriResponse *ns8__GetStreamUriResponse){return SOAP_OK;};

	/// Web service operation 'StartMulticastStreaming' (returns error code or SOAP_OK)
	virtual	int StartMulticastStreaming(_ns8__StartMulticastStreaming *ns8__StartMulticastStreaming, _ns8__StartMulticastStreamingResponse *ns8__StartMulticastStreamingResponse){return SOAP_OK;};

	/// Web service operation 'StopMulticastStreaming' (returns error code or SOAP_OK)
	virtual	int StopMulticastStreaming(_ns8__StopMulticastStreaming *ns8__StopMulticastStreaming, _ns8__StopMulticastStreamingResponse *ns8__StopMulticastStreamingResponse){return SOAP_OK;};

	/// Web service operation 'SetSynchronizationPoint' (returns error code or SOAP_OK)
	virtual	int SetSynchronizationPoint(_ns8__SetSynchronizationPoint *ns8__SetSynchronizationPoint, _ns8__SetSynchronizationPointResponse *ns8__SetSynchronizationPointResponse){return SOAP_OK;};

	/// Web service operation 'GetSnapshotUri' (returns error code or SOAP_OK)
	virtual	int GetSnapshotUri(_ns8__GetSnapshotUri *ns8__GetSnapshotUri, _ns8__GetSnapshotUriResponse *ns8__GetSnapshotUriResponse){return SOAP_OK;};

};
#endif // soapMediaBindingServiceImpl_H
