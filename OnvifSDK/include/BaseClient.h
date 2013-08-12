#ifndef BASE_CLIENT__H
#define BASE_CLIENT__H

#include "sigrlog.h"
#include "OnvifSDK.h"
#include "stringGenerator.h"

#include "DeviceClient.h"
#include "DeviceIOClient.h"
#include "DisplayClient.h"
#include "ReceiverClient.h"
#include "RecordingClient.h"

#include "WsddLib.h"

using namespace Web;

class BaseClient: IOnvifClient
{
public:
    static IOnvifClient* Instance()
    {
        static BaseClient theSingleInstance;
        return &theSingleInstance;
    }

    ~BaseClient();
    virtual int Init(const char* pchEndpoint);
    virtual std::vector<std::string> GetDiscoveredDevices();
    virtual soap* GetSoap();

    //===DEV==============================
    virtual int GetDateAndTime( /*out*/ DevGetSystemDateAndTimeResponse & );
    virtual int SetDateAndTime( DevSetSystemDateAndTime & );
    virtual int GetUsers( /*out*/ DevGetUsersResponse & );

    //===DEVIO============================
    virtual int GetVideoOutputs( /*out*/ DevIOGetVideoOutputsResponse & );

    //===DISP=============================
    virtual int GetLayout( std::string &, /*out*/ DispGetLayoutResponse & );
    virtual int GetDisplayOptions( const std::string &, DispGetDisplayOptionsResponse & );
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
    BaseClient();
    BaseClient(const BaseClient&);
    BaseClient& operator=(const BaseClient&);

    soap* m_pSoap;
    DeviceClient* m_pDevClient;
    DeviceIOClient* m_pDevIOClient;
    DisplayClient* m_pDispClient;
    ReceiverClient* m_pRecvClient;
    RecordingClient* m_pRecordingClient;
    IWsdd * m_pWsdd;
};

#endif // BASE_CLIENT__H
