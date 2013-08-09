
#include "BaseServer.h"
#include "RecordingServiceImpl.h"

int RecordingServiceImpl::CreateRecordingJob (_trc__CreateRecordingJob *trc__CreateRecordingJob,
                                              _trc__CreateRecordingJobResponse *trc__CreateRecordingJobResponse)
{
    RecCreateRecordingJob req(trc__CreateRecordingJob);
    RecCreateRecordingJobResponse resp(trc__CreateRecordingJobResponse);
    return m_pBaseServer->CreateRecordingJob(req, resp);
}

int RecordingServiceImpl::DeleteRecordingJob (_trc__DeleteRecordingJob *trc__DeleteRecordingJob,
                                              _trc__DeleteRecordingJobResponse *trc__DeleteRecordingJobResponse)
{
    RecDeleteRecordingJob r(trc__DeleteRecordingJob);
    return m_pBaseServer->DeleteRecordingJob(r.getToken());
}

int RecordingServiceImpl::CreateRecording (_trc__CreateRecording *trc__CreateRecording,
                                           _trc__CreateRecordingResponse *trc__CreateRecordingResponse)
{
    RecCreateRecording req(trc__CreateRecording);
    RecCreateRecordingResponse resp(trc__CreateRecordingResponse);
    return m_pBaseServer->CreateRecording(req, resp);
}

int RecordingServiceImpl::DeleteRecording (_trc__DeleteRecording *trc__DeleteRecording,
                                           _trc__DeleteRecordingResponse *trc__DeleteRecordingResponse)
{
    RecDeleteRecording r(trc__DeleteRecording);
    return m_pBaseServer->DeleteRecording(r.getToken());
}
