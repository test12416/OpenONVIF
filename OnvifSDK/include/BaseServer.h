#ifndef BASESERVER_H
#define BASESERVER_H

#include "sigrlog.h"
#include "OnvifSDK.h"
#include "stringGenerator.h"
#include "WsddLib.h"

#include "DeviceServiceImpl.h"
#include "DeviceIOServiceImpl.h"
#include "DisplayServiceImpl.h"
#include "ReceiverServiceImpl.h"
#include "ReplayServiceImpl.h"
#include "RecordingServiceImpl.h"
#include "SearchServiceImpl.h"

using namespace Web;

class BaseServer : public IOnvifServer,
                    public IOnvif
{
public:
    static IOnvifServer* Instance()
    {
        static BaseServer theSingleInstance;
        return &theSingleInstance;
    }

	virtual ~BaseServer();
    virtual int Init(int iServicesToHost, int port, IOnvif* pHandler);
	virtual int Run();

	//===DEV==============================
    virtual int GetDateAndTime( /*out*/ DevGetSystemDateAndTimeResponse & );
    virtual int SetDateAndTime( DevSetSystemDateAndTime & );
    virtual int GetUsers( /*out*/ DevGetUsersResponse & );

    //===DEVIO============================
    virtual int GetVideoOutputs( /*out*/ DevIOGetVideoOutputsResponse & );

    //===DISP=============================
    virtual int GetLayout( std::string &, /*out*/ DispGetLayoutResponse & );
    virtual int GetDisplayOptions( const std::string &, /*out*/ DispGetDisplayOptionsResponse & );
    virtual int SetLayout( DispSetLayout &);
    virtual int CreatePaneConfiguration( DispCreatePaneConfiguration &, /*out*/ DispCreatePaneConfigurationResponse & );

    //===RECV=============================
    virtual int GetReceivers( RecvGetReceiversResponse & );
    virtual int CreateReceiver( const std::string & uri, /*out*/ std::string & recvToken );
    virtual int SetReceiverMode( const std::string & recvToken, bool bMode );
    //===RECORDING=========================
    virtual int CreateRecording (RecCreateRecording &, RecCreateRecordingResponse &);
    virtual int CreateRecordingJob (RecCreateRecordingJob &, RecCreateRecordingJobResponse &);
    virtual int DeleteRecording (const std::string &);
    virtual int DeleteRecordingJob (const std::string &);

private:
    BaseServer();
    BaseServer(const BaseServer&);
    BaseServer& operator=(const BaseServer&);
    virtual int RunWsDiscovery();

	bool m_bCreated;
	int m_iPort;
	struct soap * m_pSoap;
	DeviceServiceImpl * m_DevService;
	DeviceIOServiceImpl * m_DevIOService;
	DisplayServiceImpl * m_DispService;
	ReceiverServiceImpl * m_RecvService;
    ReplayServiceImpl * m_ReplayService;
    RecordingServiceImpl * m_RecordService;
    SearchServiceImpl * m_SearchService;
    IWsdd* m_pWsdd;
    IOnvif* m_pHandler;
};

#endif	// BASESERVER_H
