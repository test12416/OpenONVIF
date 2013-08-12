#ifndef soapMediaBindingServiceImpl_H
#define soapMediaBindingServiceImpl_H

#include "WebMediaBindingService.h"
class OnvifServer;
namespace Web {
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
    virtual	int GetServiceCapabilities(_trt__GetServiceCapabilities *trt__GetServiceCapabilities, _trt__GetServiceCapabilitiesResponse *trt__GetServiceCapabilitiesResponse){return SOAP_OK;};

	/// Web service operation 'GetVideoSources' (returns error code or SOAP_OK)
    virtual	int GetVideoSources(_trt__GetVideoSources *trt__GetVideoSources, _trt__GetVideoSourcesResponse *trt__GetVideoSourcesResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioSources' (returns error code or SOAP_OK)
    virtual	int GetAudioSources(_trt__GetAudioSources *trt__GetAudioSources, _trt__GetAudioSourcesResponse *trt__GetAudioSourcesResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioOutputs' (returns error code or SOAP_OK)
    virtual	int GetAudioOutputs(_trt__GetAudioOutputs *trt__GetAudioOutputs, _trt__GetAudioOutputsResponse *trt__GetAudioOutputsResponse){return SOAP_OK;};

	/// Web service operation 'CreateProfile' (returns error code or SOAP_OK)
    virtual	int CreateProfile(_trt__CreateProfile *trt__CreateProfile, _trt__CreateProfileResponse *trt__CreateProfileResponse){return SOAP_OK;};

	/// Web service operation 'GetProfile' (returns error code or SOAP_OK)
    virtual	int GetProfile(_trt__GetProfile *trt__GetProfile, _trt__GetProfileResponse *trt__GetProfileResponse){return SOAP_OK;};

	/// Web service operation 'GetProfiles' (returns error code or SOAP_OK)
    virtual	int GetProfiles(_trt__GetProfiles *trt__GetProfiles, _trt__GetProfilesResponse *trt__GetProfilesResponse){return SOAP_OK;};

	/// Web service operation 'AddVideoEncoderConfiguration' (returns error code or SOAP_OK)
    virtual	int AddVideoEncoderConfiguration(_trt__AddVideoEncoderConfiguration *trt__AddVideoEncoderConfiguration, _trt__AddVideoEncoderConfigurationResponse *trt__AddVideoEncoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'AddVideoSourceConfiguration' (returns error code or SOAP_OK)
    virtual	int AddVideoSourceConfiguration(_trt__AddVideoSourceConfiguration *trt__AddVideoSourceConfiguration, _trt__AddVideoSourceConfigurationResponse *trt__AddVideoSourceConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'AddAudioEncoderConfiguration' (returns error code or SOAP_OK)
    virtual	int AddAudioEncoderConfiguration(_trt__AddAudioEncoderConfiguration *trt__AddAudioEncoderConfiguration, _trt__AddAudioEncoderConfigurationResponse *trt__AddAudioEncoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'AddAudioSourceConfiguration' (returns error code or SOAP_OK)
    virtual	int AddAudioSourceConfiguration(_trt__AddAudioSourceConfiguration *trt__AddAudioSourceConfiguration, _trt__AddAudioSourceConfigurationResponse *trt__AddAudioSourceConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'AddPTZConfiguration' (returns error code or SOAP_OK)
    virtual	int AddPTZConfiguration(_trt__AddPTZConfiguration *trt__AddPTZConfiguration, _trt__AddPTZConfigurationResponse *trt__AddPTZConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'AddVideoAnalyticsConfiguration' (returns error code or SOAP_OK)
    virtual	int AddVideoAnalyticsConfiguration(_trt__AddVideoAnalyticsConfiguration *trt__AddVideoAnalyticsConfiguration, _trt__AddVideoAnalyticsConfigurationResponse *trt__AddVideoAnalyticsConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'AddMetadataConfiguration' (returns error code or SOAP_OK)
    virtual	int AddMetadataConfiguration(_trt__AddMetadataConfiguration *trt__AddMetadataConfiguration, _trt__AddMetadataConfigurationResponse *trt__AddMetadataConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'AddAudioOutputConfiguration' (returns error code or SOAP_OK)
    virtual	int AddAudioOutputConfiguration(_trt__AddAudioOutputConfiguration *trt__AddAudioOutputConfiguration, _trt__AddAudioOutputConfigurationResponse *trt__AddAudioOutputConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'AddAudioDecoderConfiguration' (returns error code or SOAP_OK)
    virtual	int AddAudioDecoderConfiguration(_trt__AddAudioDecoderConfiguration *trt__AddAudioDecoderConfiguration, _trt__AddAudioDecoderConfigurationResponse *trt__AddAudioDecoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'RemoveVideoEncoderConfiguration' (returns error code or SOAP_OK)
    virtual	int RemoveVideoEncoderConfiguration(_trt__RemoveVideoEncoderConfiguration *trt__RemoveVideoEncoderConfiguration, _trt__RemoveVideoEncoderConfigurationResponse *trt__RemoveVideoEncoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'RemoveVideoSourceConfiguration' (returns error code or SOAP_OK)
    virtual	int RemoveVideoSourceConfiguration(_trt__RemoveVideoSourceConfiguration *trt__RemoveVideoSourceConfiguration, _trt__RemoveVideoSourceConfigurationResponse *trt__RemoveVideoSourceConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'RemoveAudioEncoderConfiguration' (returns error code or SOAP_OK)
    virtual	int RemoveAudioEncoderConfiguration(_trt__RemoveAudioEncoderConfiguration *trt__RemoveAudioEncoderConfiguration, _trt__RemoveAudioEncoderConfigurationResponse *trt__RemoveAudioEncoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'RemoveAudioSourceConfiguration' (returns error code or SOAP_OK)
    virtual	int RemoveAudioSourceConfiguration(_trt__RemoveAudioSourceConfiguration *trt__RemoveAudioSourceConfiguration, _trt__RemoveAudioSourceConfigurationResponse *trt__RemoveAudioSourceConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'RemovePTZConfiguration' (returns error code or SOAP_OK)
    virtual	int RemovePTZConfiguration(_trt__RemovePTZConfiguration *trt__RemovePTZConfiguration, _trt__RemovePTZConfigurationResponse *trt__RemovePTZConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'RemoveVideoAnalyticsConfiguration' (returns error code or SOAP_OK)
    virtual	int RemoveVideoAnalyticsConfiguration(_trt__RemoveVideoAnalyticsConfiguration *trt__RemoveVideoAnalyticsConfiguration, _trt__RemoveVideoAnalyticsConfigurationResponse *trt__RemoveVideoAnalyticsConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'RemoveMetadataConfiguration' (returns error code or SOAP_OK)
    virtual	int RemoveMetadataConfiguration(_trt__RemoveMetadataConfiguration *trt__RemoveMetadataConfiguration, _trt__RemoveMetadataConfigurationResponse *trt__RemoveMetadataConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'RemoveAudioOutputConfiguration' (returns error code or SOAP_OK)
    virtual	int RemoveAudioOutputConfiguration(_trt__RemoveAudioOutputConfiguration *trt__RemoveAudioOutputConfiguration, _trt__RemoveAudioOutputConfigurationResponse *trt__RemoveAudioOutputConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'RemoveAudioDecoderConfiguration' (returns error code or SOAP_OK)
    virtual	int RemoveAudioDecoderConfiguration(_trt__RemoveAudioDecoderConfiguration *trt__RemoveAudioDecoderConfiguration, _trt__RemoveAudioDecoderConfigurationResponse *trt__RemoveAudioDecoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'DeleteProfile' (returns error code or SOAP_OK)
    virtual	int DeleteProfile(_trt__DeleteProfile *trt__DeleteProfile, _trt__DeleteProfileResponse *trt__DeleteProfileResponse){return SOAP_OK;};

	/// Web service operation 'GetVideoSourceConfigurations' (returns error code or SOAP_OK)
    virtual	int GetVideoSourceConfigurations(_trt__GetVideoSourceConfigurations *trt__GetVideoSourceConfigurations, _trt__GetVideoSourceConfigurationsResponse *trt__GetVideoSourceConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetVideoEncoderConfigurations' (returns error code or SOAP_OK)
    virtual	int GetVideoEncoderConfigurations(_trt__GetVideoEncoderConfigurations *trt__GetVideoEncoderConfigurations, _trt__GetVideoEncoderConfigurationsResponse *trt__GetVideoEncoderConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioSourceConfigurations' (returns error code or SOAP_OK)
    virtual	int GetAudioSourceConfigurations(_trt__GetAudioSourceConfigurations *trt__GetAudioSourceConfigurations, _trt__GetAudioSourceConfigurationsResponse *trt__GetAudioSourceConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioEncoderConfigurations' (returns error code or SOAP_OK)
    virtual	int GetAudioEncoderConfigurations(_trt__GetAudioEncoderConfigurations *trt__GetAudioEncoderConfigurations, _trt__GetAudioEncoderConfigurationsResponse *trt__GetAudioEncoderConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetVideoAnalyticsConfigurations' (returns error code or SOAP_OK)
    virtual	int GetVideoAnalyticsConfigurations(_trt__GetVideoAnalyticsConfigurations *trt__GetVideoAnalyticsConfigurations, _trt__GetVideoAnalyticsConfigurationsResponse *trt__GetVideoAnalyticsConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetMetadataConfigurations' (returns error code or SOAP_OK)
    virtual	int GetMetadataConfigurations(_trt__GetMetadataConfigurations *trt__GetMetadataConfigurations, _trt__GetMetadataConfigurationsResponse *trt__GetMetadataConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioOutputConfigurations' (returns error code or SOAP_OK)
    virtual	int GetAudioOutputConfigurations(_trt__GetAudioOutputConfigurations *trt__GetAudioOutputConfigurations, _trt__GetAudioOutputConfigurationsResponse *trt__GetAudioOutputConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioDecoderConfigurations' (returns error code or SOAP_OK)
    virtual	int GetAudioDecoderConfigurations(_trt__GetAudioDecoderConfigurations *trt__GetAudioDecoderConfigurations, _trt__GetAudioDecoderConfigurationsResponse *trt__GetAudioDecoderConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetVideoSourceConfiguration' (returns error code or SOAP_OK)
    virtual	int GetVideoSourceConfiguration(_trt__GetVideoSourceConfiguration *trt__GetVideoSourceConfiguration, _trt__GetVideoSourceConfigurationResponse *trt__GetVideoSourceConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'GetVideoEncoderConfiguration' (returns error code or SOAP_OK)
    virtual	int GetVideoEncoderConfiguration(_trt__GetVideoEncoderConfiguration *trt__GetVideoEncoderConfiguration, _trt__GetVideoEncoderConfigurationResponse *trt__GetVideoEncoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioSourceConfiguration' (returns error code or SOAP_OK)
    virtual	int GetAudioSourceConfiguration(_trt__GetAudioSourceConfiguration *trt__GetAudioSourceConfiguration, _trt__GetAudioSourceConfigurationResponse *trt__GetAudioSourceConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioEncoderConfiguration' (returns error code or SOAP_OK)
    virtual	int GetAudioEncoderConfiguration(_trt__GetAudioEncoderConfiguration *trt__GetAudioEncoderConfiguration, _trt__GetAudioEncoderConfigurationResponse *trt__GetAudioEncoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'GetVideoAnalyticsConfiguration' (returns error code or SOAP_OK)
    virtual	int GetVideoAnalyticsConfiguration(_trt__GetVideoAnalyticsConfiguration *trt__GetVideoAnalyticsConfiguration, _trt__GetVideoAnalyticsConfigurationResponse *trt__GetVideoAnalyticsConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'GetMetadataConfiguration' (returns error code or SOAP_OK)
    virtual	int GetMetadataConfiguration(_trt__GetMetadataConfiguration *trt__GetMetadataConfiguration, _trt__GetMetadataConfigurationResponse *trt__GetMetadataConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioOutputConfiguration' (returns error code or SOAP_OK)
    virtual	int GetAudioOutputConfiguration(_trt__GetAudioOutputConfiguration *trt__GetAudioOutputConfiguration, _trt__GetAudioOutputConfigurationResponse *trt__GetAudioOutputConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioDecoderConfiguration' (returns error code or SOAP_OK)
    virtual	int GetAudioDecoderConfiguration(_trt__GetAudioDecoderConfiguration *trt__GetAudioDecoderConfiguration, _trt__GetAudioDecoderConfigurationResponse *trt__GetAudioDecoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'GetCompatibleVideoEncoderConfigurations' (returns error code or SOAP_OK)
    virtual	int GetCompatibleVideoEncoderConfigurations(_trt__GetCompatibleVideoEncoderConfigurations *trt__GetCompatibleVideoEncoderConfigurations, _trt__GetCompatibleVideoEncoderConfigurationsResponse *trt__GetCompatibleVideoEncoderConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetCompatibleVideoSourceConfigurations' (returns error code or SOAP_OK)
    virtual	int GetCompatibleVideoSourceConfigurations(_trt__GetCompatibleVideoSourceConfigurations *trt__GetCompatibleVideoSourceConfigurations, _trt__GetCompatibleVideoSourceConfigurationsResponse *trt__GetCompatibleVideoSourceConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetCompatibleAudioEncoderConfigurations' (returns error code or SOAP_OK)
    virtual	int GetCompatibleAudioEncoderConfigurations(_trt__GetCompatibleAudioEncoderConfigurations *trt__GetCompatibleAudioEncoderConfigurations, _trt__GetCompatibleAudioEncoderConfigurationsResponse *trt__GetCompatibleAudioEncoderConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetCompatibleAudioSourceConfigurations' (returns error code or SOAP_OK)
    virtual	int GetCompatibleAudioSourceConfigurations(_trt__GetCompatibleAudioSourceConfigurations *trt__GetCompatibleAudioSourceConfigurations, _trt__GetCompatibleAudioSourceConfigurationsResponse *trt__GetCompatibleAudioSourceConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetCompatibleVideoAnalyticsConfigurations' (returns error code or SOAP_OK)
    virtual	int GetCompatibleVideoAnalyticsConfigurations(_trt__GetCompatibleVideoAnalyticsConfigurations *trt__GetCompatibleVideoAnalyticsConfigurations, _trt__GetCompatibleVideoAnalyticsConfigurationsResponse *trt__GetCompatibleVideoAnalyticsConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetCompatibleMetadataConfigurations' (returns error code or SOAP_OK)
    virtual	int GetCompatibleMetadataConfigurations(_trt__GetCompatibleMetadataConfigurations *trt__GetCompatibleMetadataConfigurations, _trt__GetCompatibleMetadataConfigurationsResponse *trt__GetCompatibleMetadataConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetCompatibleAudioOutputConfigurations' (returns error code or SOAP_OK)
    virtual	int GetCompatibleAudioOutputConfigurations(_trt__GetCompatibleAudioOutputConfigurations *trt__GetCompatibleAudioOutputConfigurations, _trt__GetCompatibleAudioOutputConfigurationsResponse *trt__GetCompatibleAudioOutputConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'GetCompatibleAudioDecoderConfigurations' (returns error code or SOAP_OK)
    virtual	int GetCompatibleAudioDecoderConfigurations(_trt__GetCompatibleAudioDecoderConfigurations *trt__GetCompatibleAudioDecoderConfigurations, _trt__GetCompatibleAudioDecoderConfigurationsResponse *trt__GetCompatibleAudioDecoderConfigurationsResponse){return SOAP_OK;};

	/// Web service operation 'SetVideoSourceConfiguration' (returns error code or SOAP_OK)
    virtual	int SetVideoSourceConfiguration(_trt__SetVideoSourceConfiguration *trt__SetVideoSourceConfiguration, _trt__SetVideoSourceConfigurationResponse *trt__SetVideoSourceConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'SetVideoEncoderConfiguration' (returns error code or SOAP_OK)
    virtual	int SetVideoEncoderConfiguration(_trt__SetVideoEncoderConfiguration *trt__SetVideoEncoderConfiguration, _trt__SetVideoEncoderConfigurationResponse *trt__SetVideoEncoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'SetAudioSourceConfiguration' (returns error code or SOAP_OK)
    virtual	int SetAudioSourceConfiguration(_trt__SetAudioSourceConfiguration *trt__SetAudioSourceConfiguration, _trt__SetAudioSourceConfigurationResponse *trt__SetAudioSourceConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'SetAudioEncoderConfiguration' (returns error code or SOAP_OK)
    virtual	int SetAudioEncoderConfiguration(_trt__SetAudioEncoderConfiguration *trt__SetAudioEncoderConfiguration, _trt__SetAudioEncoderConfigurationResponse *trt__SetAudioEncoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'SetVideoAnalyticsConfiguration' (returns error code or SOAP_OK)
    virtual	int SetVideoAnalyticsConfiguration(_trt__SetVideoAnalyticsConfiguration *trt__SetVideoAnalyticsConfiguration, _trt__SetVideoAnalyticsConfigurationResponse *trt__SetVideoAnalyticsConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'SetMetadataConfiguration' (returns error code or SOAP_OK)
    virtual	int SetMetadataConfiguration(_trt__SetMetadataConfiguration *trt__SetMetadataConfiguration, _trt__SetMetadataConfigurationResponse *trt__SetMetadataConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'SetAudioOutputConfiguration' (returns error code or SOAP_OK)
    virtual	int SetAudioOutputConfiguration(_trt__SetAudioOutputConfiguration *trt__SetAudioOutputConfiguration, _trt__SetAudioOutputConfigurationResponse *trt__SetAudioOutputConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'SetAudioDecoderConfiguration' (returns error code or SOAP_OK)
    virtual	int SetAudioDecoderConfiguration(_trt__SetAudioDecoderConfiguration *trt__SetAudioDecoderConfiguration, _trt__SetAudioDecoderConfigurationResponse *trt__SetAudioDecoderConfigurationResponse){return SOAP_OK;};

	/// Web service operation 'GetVideoSourceConfigurationOptions' (returns error code or SOAP_OK)
    virtual	int GetVideoSourceConfigurationOptions(_trt__GetVideoSourceConfigurationOptions *trt__GetVideoSourceConfigurationOptions, _trt__GetVideoSourceConfigurationOptionsResponse *trt__GetVideoSourceConfigurationOptionsResponse){return SOAP_OK;};

	/// Web service operation 'GetVideoEncoderConfigurationOptions' (returns error code or SOAP_OK)
    virtual	int GetVideoEncoderConfigurationOptions(_trt__GetVideoEncoderConfigurationOptions *trt__GetVideoEncoderConfigurationOptions, _trt__GetVideoEncoderConfigurationOptionsResponse *trt__GetVideoEncoderConfigurationOptionsResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioSourceConfigurationOptions' (returns error code or SOAP_OK)
    virtual	int GetAudioSourceConfigurationOptions(_trt__GetAudioSourceConfigurationOptions *trt__GetAudioSourceConfigurationOptions, _trt__GetAudioSourceConfigurationOptionsResponse *trt__GetAudioSourceConfigurationOptionsResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioEncoderConfigurationOptions' (returns error code or SOAP_OK)
    virtual	int GetAudioEncoderConfigurationOptions(_trt__GetAudioEncoderConfigurationOptions *trt__GetAudioEncoderConfigurationOptions, _trt__GetAudioEncoderConfigurationOptionsResponse *trt__GetAudioEncoderConfigurationOptionsResponse){return SOAP_OK;};

	/// Web service operation 'GetMetadataConfigurationOptions' (returns error code or SOAP_OK)
    virtual	int GetMetadataConfigurationOptions(_trt__GetMetadataConfigurationOptions *trt__GetMetadataConfigurationOptions, _trt__GetMetadataConfigurationOptionsResponse *trt__GetMetadataConfigurationOptionsResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioOutputConfigurationOptions' (returns error code or SOAP_OK)
    virtual	int GetAudioOutputConfigurationOptions(_trt__GetAudioOutputConfigurationOptions *trt__GetAudioOutputConfigurationOptions, _trt__GetAudioOutputConfigurationOptionsResponse *trt__GetAudioOutputConfigurationOptionsResponse){return SOAP_OK;};

	/// Web service operation 'GetAudioDecoderConfigurationOptions' (returns error code or SOAP_OK)
    virtual	int GetAudioDecoderConfigurationOptions(_trt__GetAudioDecoderConfigurationOptions *trt__GetAudioDecoderConfigurationOptions, _trt__GetAudioDecoderConfigurationOptionsResponse *trt__GetAudioDecoderConfigurationOptionsResponse){return SOAP_OK;};

	/// Web service operation 'GetGuaranteedNumberOfVideoEncoderInstances' (returns error code or SOAP_OK)
    virtual	int GetGuaranteedNumberOfVideoEncoderInstances(_trt__GetGuaranteedNumberOfVideoEncoderInstances *trt__GetGuaranteedNumberOfVideoEncoderInstances, _trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse *trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse){return SOAP_OK;};

	/// Web service operation 'GetStreamUri' (returns error code or SOAP_OK)
    virtual	int GetStreamUri(_trt__GetStreamUri *trt__GetStreamUri, _trt__GetStreamUriResponse *trt__GetStreamUriResponse){return SOAP_OK;};

	/// Web service operation 'StartMulticastStreaming' (returns error code or SOAP_OK)
    virtual	int StartMulticastStreaming(_trt__StartMulticastStreaming *trt__StartMulticastStreaming, _trt__StartMulticastStreamingResponse *trt__StartMulticastStreamingResponse){return SOAP_OK;};

	/// Web service operation 'StopMulticastStreaming' (returns error code or SOAP_OK)
    virtual	int StopMulticastStreaming(_trt__StopMulticastStreaming *trt__StopMulticastStreaming, _trt__StopMulticastStreamingResponse *trt__StopMulticastStreamingResponse){return SOAP_OK;};

	/// Web service operation 'SetSynchronizationPoint' (returns error code or SOAP_OK)
    virtual	int SetSynchronizationPoint(_trt__SetSynchronizationPoint *trt__SetSynchronizationPoint, _trt__SetSynchronizationPointResponse *trt__SetSynchronizationPointResponse){return SOAP_OK;};

	/// Web service operation 'GetSnapshotUri' (returns error code or SOAP_OK)
    virtual	int GetSnapshotUri(_trt__GetSnapshotUri *trt__GetSnapshotUri, _trt__GetSnapshotUriResponse *trt__GetSnapshotUriResponse){return SOAP_OK;};

};
} // namespace Web
#endif // soapMediaBindingServiceImpl_H
