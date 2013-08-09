
#include "RecordingClient.h"

RecordingClient::RecordingClient(const char * pchAdress, soap * s):m_proxy(s)
{
    m_proxy.soap_endpoint = pchAdress;
}

RecordingClient::~RecordingClient()
{
}

int RecordingClient::CreateRecording (RecCreateRecording & req, RecCreateRecordingResponse & resp)
{
    int iRet = m_proxy.CreateRecording(req.d, resp.d);
    CHECKRETURN(iRet, "RecordingClient::CreateRecording");
}

int RecordingClient::CreateRecordingJob (RecCreateRecordingJob & req, RecCreateRecordingJobResponse &resp)
{
    int iRet = m_proxy.CreateRecordingJob(req.d, resp.d);
    CHECKRETURN(iRet, "RecordingClient::CreateReceiverJob");
}

int RecordingClient::DeleteRecording (const std::string & token)
{
    RecDeleteRecording r (m_proxy.soap);
    r.setToken(token);
    RecDeleteRecordingResponse resp (m_proxy.soap);
    int iRet = m_proxy.DeleteRecording(r.d, resp.d);
    CHECKRETURN(iRet, "RecordingClient::DeleteRecording");
}

int RecordingClient::DeleteRecordingJob (const std::string & token)
{
    RecDeleteRecordingJob r(m_proxy.soap);
    r.setToken(token);

    RecDeleteRecordingJobResponse resp(m_proxy.soap);
    int iRet = m_proxy.DeleteRecordingJob(r.d, resp.d);
    CHECKRETURN(iRet, "RecordingClient::DeleteRecordingJob");
}
