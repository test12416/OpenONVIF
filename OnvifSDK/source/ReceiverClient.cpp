#include "ReceiverClient.h"

namespace Web {
ReceiverClient::ReceiverClient(const char * pchAdress, soap * s):m_proxy(s)
{
	m_proxy.soap_endpoint = pchAdress;
}

ReceiverClient::~ReceiverClient()
{

}

int ReceiverClient::GetReceivers(RecvGetReceiversResponse & resp)
{
	RecvGetReceivers req(m_proxy.soap);
	
	int nRes = m_proxy.GetReceivers(req.d, resp.d);

    CHECKRETURN(nRes, "ReceiverClient::GetReceivers");
}

int ReceiverClient::CreateReceiver(const std::string &uri, std::string & recvToken)
{
    RecvCreateReceiver req(m_proxy.soap);
    RecvCreateReceiverResponse resp(m_proxy.soap);

    req.setUri(uri);
    req.setMode(0);

    int nRes = m_proxy.CreateReceiver(req.d, resp.d);
    recvToken = resp.getToken();
    CHECKRETURN(nRes, "ReceiverClient::CreateReceiver");
}

int ReceiverClient::SetReceiverMode(const std::string & recvToken, bool bMode)
{
    RecvSetReceiverMode req(m_proxy.soap);
    RecvSetReceiverModeResponse resp(m_proxy.soap);

    req.setToken(recvToken);
    req.setMode(bMode);

    SIGRLOG(SIGRDEBUG2, "ReceiverClient::SetReceiverMode %s %d", req.getToken().c_str(), req.getMode());

    int nRes = m_proxy.SetReceiverMode(req.d, resp.d);
    CHECKRETURN(nRes, "ReceiverClient::SetReceiverMode");
}
} // namespace Web
