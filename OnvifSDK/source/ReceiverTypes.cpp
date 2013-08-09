
#include "OnvifSDK.h"
#include "commonTypes.h"
#include "soapReceiverBindingProxy.h"

#define EXTRA_CONSTRUCT() \
{\
}

CLASS_CTORS(trv, Recv, GetReceivers)
CLASS_CTORS(trv, Recv, GetReceiversResponse)

int RecvGetReceiversResponse::SetReceivers(std::string & str)
{
	tt__Receiver * recv = soap_new_tt__Receiver(this->d->soap, -1);
	
	recv->Token = str;

	this->d->Receivers.push_back(recv);

	return 0;
}

int RecvGetReceiversResponse::GetReceivers(std::string & str) const
{
	str = this->d->Receivers[0]->Token;

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
#define EXTRA_CONSTRUCT() \
{\
    if(d->Configuration == NULL)\
    {\
        d->Configuration = soap_new_tt__ReceiverConfiguration( d->soap );\
        d->Configuration->StreamSetup = soap_new_tt__StreamSetup( d->soap );\
        d->Configuration->StreamSetup->Transport = soap_new_tt__Transport( d->soap );\
        d->Configuration->StreamSetup->Stream = tt__StreamType__RTP_Unicast;\
        d->Configuration->StreamSetup->Transport->Protocol = tt__TransportProtocol__RTSP;\
    }\
}

CLASS_CTORS(trv, Recv, CreateReceiver)

bool RecvCreateReceiver::getMode() const
{
    return d->Configuration->Mode == tt__ReceiverMode__AlwaysConnect;
}

void RecvCreateReceiver::setMode( bool bMode)
{
    if(bMode)
        d->Configuration->Mode = tt__ReceiverMode__AlwaysConnect;
    else
        d->Configuration->Mode = tt__ReceiverMode__NeverConnect;
}

std::string RecvCreateReceiver::getUri() const
{
    return d->Configuration->MediaUri;
}
void RecvCreateReceiver::setUri( const std::string & str )
{
    d->Configuration->MediaUri = str;
}

#define EXTRA_CONSTRUCT() \
{\
    if(d->Receiver == NULL)\
    {\
        d->Receiver = soap_new_tt__Receiver( d->soap );\
        d->Receiver->Configuration = soap_new_tt__ReceiverConfiguration( d->soap );\
        d->Receiver->Configuration->StreamSetup = soap_new_tt__StreamSetup( d->soap );\
        d->Receiver->Configuration->StreamSetup->Transport = soap_new_tt__Transport( d->soap );\
        d->Receiver->Configuration->StreamSetup->Stream = tt__StreamType__RTP_Unicast;\
        d->Receiver->Configuration->StreamSetup->Transport->Protocol = tt__TransportProtocol__RTSP;\
    }\
}

CLASS_CTORS(trv, Recv, CreateReceiverResponse)

void RecvCreateReceiverResponse::setToken( const std::string & str )
{
    d->Receiver->Token = str;
}

std::string RecvCreateReceiverResponse::getToken() const
{
    return d->Receiver->Token;
}

////////////////////////////////////////////////////////////////////////////////
#define EXTRA_CONSTRUCT() \
{\
}

CLASS_CTORS(trv, Recv, SetReceiverMode)
CLASS_CTORS(trv, Recv, SetReceiverModeResponse)

bool RecvSetReceiverMode::getMode() const
{
    return d->Mode == tt__ReceiverMode__AlwaysConnect;
}

std::string RecvSetReceiverMode::getToken() const
{
    return d->ReceiverToken;
}

void RecvSetReceiverMode::setMode( bool bMode)
{
    if(bMode)
        d->Mode = tt__ReceiverMode__AlwaysConnect;
    else
        d->Mode = tt__ReceiverMode__NeverConnect;
}

void RecvSetReceiverMode::setToken( const std::string & str)
{
    d->ReceiverToken = str;
}
