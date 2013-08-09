#ifndef RECEIVERCLIENT_H
#define RECEIVERCLIENT_H

#include "sigrlog.h"
#include "OnvifSDK.h"
#include "soapReceiverBindingProxy.h"

class ReceiverClient
{
public:
	ReceiverClient(const char * pchAdress, soap * s);
	~ReceiverClient();

    int GetReceivers( RecvGetReceiversResponse & );
    int CreateReceiver( const std::string & uri, std::string & recvToken );
    int SetReceiverMode( const std::string & recvToken, bool bMode );

private:
	ReceiverBindingProxy m_proxy;
};

#endif	// RECEIVERCLIENT_H
