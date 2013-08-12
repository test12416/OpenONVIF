
#include "BaseServer.h"

using namespace Web;

static GeneratorInitializer generatorInitializer;

std::string GenerateToken()
{
    std::string str;

    for(unsigned int i = 0; i < TOKEN_LEN; ++i)
        str += alphanum[rand() % stringLength];

    return str;
};

IOnvifServer* getOnvifServer()
{
    return BaseServer::Instance();
}

BaseServer::BaseServer():
    m_pWsdd(NULL),
    m_pSoap(soap_new())
{
}

int BaseServer::Init(int iServicesToHost, int iPort, IOnvif *pHandler)
{
    m_pHandler = pHandler;
    m_iPort = iPort;
    m_DevService     = (iServicesToHost & DEV_S)    ? new DeviceServiceImpl(this, m_pSoap)   : NULL;
    m_DevIOService   = (iServicesToHost & DEVIO_S)  ? new DeviceIOServiceImpl(this, m_pSoap) : NULL;
    m_DispService    = (iServicesToHost & DISP_S)   ? new DisplayServiceImpl(this, m_pSoap)  : NULL;
    m_RecvService    = (iServicesToHost & RECV_S)   ? new ReceiverServiceImpl(this, m_pSoap) : NULL;
    m_ReplayService  = (iServicesToHost & REPLAY_S) ? new ReplayServiceImpl(this, m_pSoap)   : NULL;
    m_RecordService  = (iServicesToHost & RECORD_S) ? new RecordingServiceImpl(this, m_pSoap): NULL;
    m_SearchService  = (iServicesToHost & SEARCH_S) ? new SearchServiceImpl(this, m_pSoap)   : NULL;

    int iRet = RunWsDiscovery();
    if(iRet != 0)
            SIGRLOG (SIGRWARNING, "BaseServer::Run RunWsDiscovery failed");

    m_bCreated = m_pSoap && m_DevService && m_pHandler && (iRet == 0);
    return m_bCreated ? 0 : -1;
}

BaseServer::~BaseServer()
{
    if(m_pWsdd)
        m_pWsdd->stop();

    if(m_RecvService)
        delete m_RecvService;
    if(m_DispService)
        delete m_DispService;
    if(m_DevIOService)
        delete m_DevIOService;
    if(m_DevService)
        delete m_DevService;
    if(m_ReplayService)
        delete m_ReplayService;
    if(m_RecordService)
        delete m_RecordService;
    if(m_SearchService)
        delete m_SearchService;

    if(m_pSoap)
    {
        soap_destroy(m_pSoap);
        soap_end(m_pSoap);
        soap_free(m_pSoap);
    }
}

int BaseServer::Run()
{
    if(!m_bCreated)
    {
        SIGRLOG(SIGRCRITICAL, "BaseServer::Run Services were not created");
        return -1;
    }    

    int iRet = soap_bind(m_pSoap, NULL, m_iPort, 100);

    if (iRet == SOAP_INVALID_SOCKET)
    {
        SIGRLOG(SIGRCRITICAL, "BaseServer::Run Binding on %d port failed", m_iPort);
        return -1;
    }

    while(1)
    {
        iRet = soap_accept(m_pSoap);
        if (iRet == SOAP_INVALID_SOCKET)
        {
            SIGRLOG(SIGRCRITICAL, "BaseServer::Run accepting failed");
            return -1;
        }

        if (soap_begin_serve(m_pSoap) != SOAP_OK)
            SIGRLOG(SIGRWARNING, "BaseServer::Run serve failed");

        if (m_DevService)
            iRet = m_DevService->dispatch();

        if (iRet == SOAP_OK)
            continue;

        if (m_DevIOService)
            iRet = m_DevIOService->dispatch();

        if (iRet == SOAP_OK)
            continue;

        if (m_DispService)
            iRet = m_DispService->dispatch();

        if (iRet == SOAP_OK)
            continue;

        if (m_RecvService)
            iRet = m_RecvService->dispatch();

        if (iRet == SOAP_OK)
            continue;

        if (m_ReplayService)
            iRet = m_ReplayService->dispatch();

        if (iRet == SOAP_OK)
            continue;

        if (m_RecordService)
            iRet = m_RecordService->dispatch();

        if (iRet == SOAP_OK)
            continue;

        if (m_SearchService)
            iRet = m_SearchService->dispatch();

        if(iRet != SOAP_OK)
            SIGRLOG(SIGRWARNING, "BaseServer::Run SOAP_Error= %d", iRet);
    }

    return 0;
}

int BaseServer::RunWsDiscovery()
{
    m_pWsdd = getWsdd();

    if(!m_pWsdd)
        return -1;
    int iRet = m_pWsdd->start(true);
    return iRet;
}

int BaseServer::GetDateAndTime( DevGetSystemDateAndTimeResponse & r)
{
    return m_pHandler->GetDateAndTime(r);
}

int BaseServer::SetDateAndTime( DevSetSystemDateAndTime & r)
{
    return m_pHandler->SetDateAndTime(r);
}

int BaseServer::GetUsers( /*out*/ DevGetUsersResponse & r)
{
    return m_pHandler->GetUsers(r);
}

//===DEVIO============================
int BaseServer::GetVideoOutputs( /*out*/ DevIOGetVideoOutputsResponse & r)
{
    return m_pHandler->GetVideoOutputs(r);
}

//===DISP=============================
int BaseServer::GetLayout( std::string & token, /*out*/ DispGetLayoutResponse & resp)
{
    return m_pHandler->GetLayout(token, resp);
}

int BaseServer::GetDisplayOptions( const std::string & token, DispGetDisplayOptionsResponse & resp)
{
    return m_pHandler->GetDisplayOptions(token, resp);
}

int BaseServer::SetLayout(DispSetLayout &r)
{
    return m_pHandler->SetLayout(r);
}

int BaseServer::CreatePaneConfiguration( DispCreatePaneConfiguration & req, /*out*/ DispCreatePaneConfigurationResponse & resp)
{
    return m_pHandler->CreatePaneConfiguration(req, resp);
}

//===RECV=============================
int BaseServer::GetReceivers( RecvGetReceiversResponse & r)
{
    return m_pHandler->GetReceivers(r);
}

int BaseServer::CreateReceiver( const std::string & uri, /*out*/ std::string & recvToken )
{
    return m_pHandler->CreateReceiver(uri, recvToken);
}

int BaseServer::SetReceiverMode( const std::string & recvToken, bool bMode )
{
    return m_pHandler->SetReceiverMode(recvToken, bMode);
}
//===RECORDING=========================
int BaseServer::CreateRecording (RecCreateRecording & req, RecCreateRecordingResponse & resp)
{
    return m_pHandler->CreateRecording(req, resp);
}

int BaseServer::CreateRecordingJob (RecCreateRecordingJob & req, RecCreateRecordingJobResponse & resp)
{
    return m_pHandler->CreateRecordingJob(req, resp);
}

int BaseServer::DeleteRecording (const std::string & str)
{
    return m_pHandler->DeleteRecording(str);
}

int BaseServer::DeleteRecordingJob (const std::string &str)
{
    return m_pHandler->DeleteRecordingJob(str);
}
