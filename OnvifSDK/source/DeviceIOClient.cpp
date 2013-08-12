
#include "DeviceIOClient.h"

namespace Web {
DeviceIOClient::DeviceIOClient(const char * pchAdress, soap * s):m_proxy(s)
{
	m_proxy.soap_endpoint = pchAdress;
}

DeviceIOClient::~DeviceIOClient()
{

}

int DeviceIOClient::GetVideoOutputs(DevIOGetVideoOutputsResponse & resp)
{
	DevIOGetVideoOutputs req(m_proxy.soap);

	int nRes = m_proxy.GetVideoOutputs(req.d, resp.d);
	
	CHECKRETURN(nRes, "DeviceIOClient::GetVideoOutputs");
}
} // namespace Web
