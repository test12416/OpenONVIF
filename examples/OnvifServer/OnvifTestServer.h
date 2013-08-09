#ifndef ONVIFTESTSERVER_H
#define ONVIFTESTSERVER_H

#include "OnvifSDK.h"

class OnvifTestServer : public IOnvif
{
public:
    //===DEV==============================
    virtual int GetDateAndTime( /*out*/ DevGetSystemDateAndTimeResponse & );
    virtual int SetDateAndTime( DevSetSystemDateAndTime & ){ return -1; }
    virtual int GetUsers( /*out*/ DevGetUsersResponse & ){ return -1; }
    //===DEVIO============================
    virtual int GetVideoOutputs( /*out*/ DevIOGetVideoOutputsResponse & ){ return -1; }
    //===DISP=============================
    virtual int GetLayout( std::string &, /*out*/ DispGetLayoutResponse & ){ return -1; }
    virtual int GetDisplayOptions( const std::string &, DispGetDisplayOptionsResponse & ){ return -1; }
    virtual int SetLayout( /*out*/ DispSetLayout &){ return -1; }
    virtual int CreatePaneConfiguration( DispCreatePaneConfiguration &, /*out*/ DispCreatePaneConfigurationResponse & ){ return -1; }
    //===RECV=============================
    virtual int GetReceivers( RecvGetReceiversResponse & ){ return -1; }
    virtual int CreateReceiver( const std::string & uri, /*out*/ std::string & recvToken ){ return -1; }
    virtual int SetReceiverMode( const std::string & recvToken, bool bMode ){ return -1; }
    //===RECORDING=========================
    virtual int CreateRecording (RecCreateRecording &, RecCreateRecordingResponse &){ return -1; }
    virtual int CreateRecordingJob (RecCreateRecordingJob &, RecCreateRecordingJobResponse &){ return -1; }
    virtual int DeleteRecording (const std::string &){ return -1; }
    virtual int DeleteRecordingJob (const std::string &){ return -1; }
};

#endif	// ONVIFTESTSERVER_H
