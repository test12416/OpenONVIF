#ifndef RecordingServiceImpl_H
#define RecordingServiceImpl_H

#include "WebRecordingBindingService.h"
class BaseServer;
namespace Web {
class RecordingServiceImpl : public RecordingBindingService
{
private:
    BaseServer * m_pBaseServer;
public:
    RecordingServiceImpl(BaseServer * pBaseServer, struct soap * pData):
        m_pBaseServer(pBaseServer),
        RecordingBindingService(pData)
    {
    }

    virtual	RecordingBindingService *copy() { return NULL; }

    /// Web service operation 'GetServiceCapabilities' (returns error code or SOAP_OK)
    virtual	int GetServiceCapabilities(_trc__GetServiceCapabilities *trc__GetServiceCapabilities, _trc__GetServiceCapabilitiesResponse *trc__GetServiceCapabilitiesResponse) { return SOAP_OK; }

    /// Web service operation 'CreateRecording' (returns error code or SOAP_OK)
    virtual	int CreateRecording(_trc__CreateRecording *trc__CreateRecording, _trc__CreateRecordingResponse *trc__CreateRecordingResponse);

    /// Web service operation 'DeleteRecording' (returns error code or SOAP_OK)
    virtual	int DeleteRecording(_trc__DeleteRecording *trc__DeleteRecording, _trc__DeleteRecordingResponse *trc__DeleteRecordingResponse);

    /// Web service operation 'GetRecordings' (returns error code or SOAP_OK)
    virtual	int GetRecordings(_trc__GetRecordings *trc__GetRecordings, _trc__GetRecordingsResponse *trc__GetRecordingsResponse) { return SOAP_OK; }

    /// Web service operation 'SetRecordingConfiguration' (returns error code or SOAP_OK)
    virtual	int SetRecordingConfiguration(_trc__SetRecordingConfiguration *trc__SetRecordingConfiguration, _trc__SetRecordingConfigurationResponse *trc__SetRecordingConfigurationResponse) { return SOAP_OK; }

    /// Web service operation 'GetRecordingConfiguration' (returns error code or SOAP_OK)
    virtual	int GetRecordingConfiguration(_trc__GetRecordingConfiguration *trc__GetRecordingConfiguration, _trc__GetRecordingConfigurationResponse *trc__GetRecordingConfigurationResponse) { return SOAP_OK; }

    /// Web service operation 'GetRecordingOptions' (returns error code or SOAP_OK)
    virtual	int GetRecordingOptions(_trc__GetRecordingOptions *trc__GetRecordingOptions, _trc__GetRecordingOptionsResponse *trc__GetRecordingOptionsResponse) { return SOAP_OK; }

    /// Web service operation 'CreateTrack' (returns error code or SOAP_OK)
    virtual	int CreateTrack(_trc__CreateTrack *trc__CreateTrack, _trc__CreateTrackResponse *trc__CreateTrackResponse) { return SOAP_OK; }

    /// Web service operation 'DeleteTrack' (returns error code or SOAP_OK)
    virtual	int DeleteTrack(_trc__DeleteTrack *trc__DeleteTrack, _trc__DeleteTrackResponse *trc__DeleteTrackResponse) { return SOAP_OK; }

    /// Web service operation 'GetTrackConfiguration' (returns error code or SOAP_OK)
    virtual	int GetTrackConfiguration(_trc__GetTrackConfiguration *trc__GetTrackConfiguration, _trc__GetTrackConfigurationResponse *trc__GetTrackConfigurationResponse) { return SOAP_OK; }

    /// Web service operation 'SetTrackConfiguration' (returns error code or SOAP_OK)
    virtual	int SetTrackConfiguration(_trc__SetTrackConfiguration *trc__SetTrackConfiguration, _trc__SetTrackConfigurationResponse *trc__SetTrackConfigurationResponse) { return SOAP_OK; }

    /// Web service operation 'CreateRecordingJob' (returns error code or SOAP_OK)
    virtual	int CreateRecordingJob(_trc__CreateRecordingJob *trc__CreateRecordingJob, _trc__CreateRecordingJobResponse *trc__CreateRecordingJobResponse);

    /// Web service operation 'DeleteRecordingJob' (returns error code or SOAP_OK)
    virtual	int DeleteRecordingJob(_trc__DeleteRecordingJob *trc__DeleteRecordingJob, _trc__DeleteRecordingJobResponse *trc__DeleteRecordingJobResponse);

    /// Web service operation 'GetRecordingJobs' (returns error code or SOAP_OK)
    virtual	int GetRecordingJobs(_trc__GetRecordingJobs *trc__GetRecordingJobs, _trc__GetRecordingJobsResponse *trc__GetRecordingJobsResponse) { return SOAP_OK; }

    /// Web service operation 'SetRecordingJobConfiguration' (returns error code or SOAP_OK)
    virtual	int SetRecordingJobConfiguration(_trc__SetRecordingJobConfiguration *trc__SetRecordingJobConfiguration, _trc__SetRecordingJobConfigurationResponse *trc__SetRecordingJobConfigurationResponse) { return SOAP_OK; }

    /// Web service operation 'GetRecordingJobConfiguration' (returns error code or SOAP_OK)
    virtual	int GetRecordingJobConfiguration(_trc__GetRecordingJobConfiguration *trc__GetRecordingJobConfiguration, _trc__GetRecordingJobConfigurationResponse *trc__GetRecordingJobConfigurationResponse) { return SOAP_OK; }

    /// Web service operation 'SetRecordingJobMode' (returns error code or SOAP_OK)
    virtual	int SetRecordingJobMode(_trc__SetRecordingJobMode *trc__SetRecordingJobMode, _trc__SetRecordingJobModeResponse *trc__SetRecordingJobModeResponse) { return SOAP_OK; }

    /// Web service operation 'GetRecordingJobState' (returns error code or SOAP_OK)
    virtual	int GetRecordingJobState(_trc__GetRecordingJobState *trc__GetRecordingJobState, _trc__GetRecordingJobStateResponse *trc__GetRecordingJobStateResponse) { return SOAP_OK; }


};
} // namespace Web
#endif // RecordingServiceImpl_H
