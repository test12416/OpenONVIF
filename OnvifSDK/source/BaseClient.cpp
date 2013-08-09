
#include "BaseClient.h"

IOnvifClient* getOnvifClient()
{
    return BaseClient::Instance();
}

BaseClient::BaseClient():
    m_pSoap (soap_new()),
    m_pWsdd (getWsdd())
{
}

BaseClient::~BaseClient()
{
    if (m_pDevClient)
         delete m_pDevClient;
    if (m_pDevIOClient)
        delete m_pDevIOClient;
    if (m_pDispClient)
        delete m_pDispClient;
    if (m_pRecvClient)
        delete m_pRecvClient;

     if(m_pSoap)
     {
         soap_destroy(m_pSoap);
         soap_end(m_pSoap);
         soap_free(m_pSoap);
     }
}

soap* BaseClient::GetSoap()
{
    return m_pSoap;
}


int BaseClient::Init(const char* pchEndpoint)
{
    if(!m_pSoap || !m_pWsdd)
        return -1;

    m_pWsdd->start(false);

    m_pDevClient = new DeviceClient (pchEndpoint, m_pSoap);
    m_pDevIOClient = new DeviceIOClient (pchEndpoint, m_pSoap);
    m_pDispClient = new DisplayClient (pchEndpoint, m_pSoap);
    m_pRecvClient = new ReceiverClient (pchEndpoint, m_pSoap);
    m_pRecordingClient = new RecordingClient (pchEndpoint, m_pSoap);

    return m_pDevClient && m_pDevClient && m_pDispClient && m_pRecvClient ? 0 : -1;
}

std::vector<std::string> BaseClient::GetDiscoveredDevices()
{
    return m_pWsdd->getMembers();
}

int BaseClient::GetDateAndTime(DevGetSystemDateAndTimeResponse & r)
{
    return m_pDevClient->GetDateAndTime(r);
}

int BaseClient::SetDateAndTime( DevSetSystemDateAndTime & r)
{
    return m_pDevClient->SetDateAndTime(r);
}

int BaseClient::GetUsers(DevGetUsersResponse & r)
{
    return m_pDevClient->GetUsers(r);
}

//int BaseClient::GetServices(DevGetServicesResponse &r)
//{
//    return m_pDevClient->GetServices(r);
//}

int BaseClient::GetVideoOutputs(DevIOGetVideoOutputsResponse & r)
{
    return m_pDevIOClient->GetVideoOutputs(r);
}

int BaseClient::GetLayout( std::string & token, DispGetLayoutResponse & resp)
{
    DispGetLayout req(m_pSoap);
    req.SetLayout(token);
    return m_pDispClient->GetLayout(req, resp);
}

int BaseClient::GetDisplayOptions(const std::string & voToken, DispGetDisplayOptionsResponse & resp)
{
    DispGetDisplayOptions req(m_pSoap);
    req.SetVO(voToken);
    return m_pDispClient->GetDisplayOptions(req, resp);
}

int BaseClient::SetLayout(DispSetLayout & r)
{
    return m_pDispClient->SetLayout(r);
}

int BaseClient::CreatePaneConfiguration(DispCreatePaneConfiguration & req, DispCreatePaneConfigurationResponse & resp)
{
    return m_pDispClient->CreatePaneConfiguration(req, resp);
}

int BaseClient::GetReceivers( RecvGetReceiversResponse & r)
{
    return m_pRecvClient->GetReceivers(r);
}

int BaseClient::CreateReceiver(const std::string & uri, std::string & recvToken )
{
    return m_pRecvClient->CreateReceiver( uri, recvToken);
}

int BaseClient::SetReceiverMode( const std::string & recvToken, bool bMode )
{
    return m_pRecvClient->SetReceiverMode(recvToken, bMode);
}

int BaseClient::CreateRecording (RecCreateRecording & req, RecCreateRecordingResponse & resp)
{
    return m_pRecordingClient->CreateRecording(req, resp);
}

int BaseClient::CreateRecordingJob (RecCreateRecordingJob & req, RecCreateRecordingJobResponse & resp)
{
    return m_pRecordingClient->CreateRecordingJob(req, resp);
}

int BaseClient::DeleteRecording (const std::string &s)
{
    return m_pRecordingClient->DeleteRecording(s);
}

int BaseClient::DeleteRecordingJob (const std::string &s)
{
    return m_pRecordingClient->DeleteRecordingJob(s);
}
