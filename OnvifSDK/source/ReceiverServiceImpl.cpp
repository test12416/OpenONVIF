
#include "sigrlog.h"
#include "ReceiverServiceImpl.h"
#include "BaseServer.h"

// for while not supporting copy
ReceiverBindingService* ReceiverServiceImpl::copy()
{
        return NULL;
}

int ReceiverServiceImpl::GetReceivers(_trv__GetReceivers *trv__GetReceivers, _trv__GetReceiversResponse *trv__GetReceiversResponse)
{
	RecvGetReceiversResponse resp( trv__GetReceiversResponse );

    int nRes = m_pBaseServer->GetReceivers(resp);

	CHECKRETURN(nRes, "ReceiverServiceImpl::GetReceivers");
}

int ReceiverServiceImpl::CreateReceiver(_trv__CreateReceiver *trv__CreateReceiver, _trv__CreateReceiverResponse *trv__CreateReceiverResponse)
{
    RecvCreateReceiver req(trv__CreateReceiver);
    RecvCreateReceiverResponse resp(trv__CreateReceiverResponse);

    std::string recvToken;

    int nRes = m_pBaseServer->CreateReceiver( req.getUri(), recvToken );

    resp.setToken(recvToken);

    CHECKRETURN(nRes, "ReceiverServiceImpl::CreateReceiver");
}

int ReceiverServiceImpl::SetReceiverMode(_trv__SetReceiverMode *trv__SetReceiverMode, _trv__SetReceiverModeResponse *trv__SetReceiverModeResponse)
{
    RecvSetReceiverMode req(trv__SetReceiverMode);

    int nRes = m_pBaseServer->SetReceiverMode( req.getToken(), req.getMode() );
    CHECKRETURN(nRes, "ReceiverServiceImpl::SetReceiverMode");
}
