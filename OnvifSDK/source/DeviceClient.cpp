
#include "DeviceClient.h"

namespace Web {
DeviceClient::DeviceClient(const char * pchAdress, soap * s):m_proxy(s)
{
	m_proxy.soap_endpoint = pchAdress;
}

DeviceClient::~DeviceClient()
{

}

int DeviceClient::GetDateAndTime(DevGetSystemDateAndTimeResponse & resp)
{	
	DevGetSystemDateAndTime req(m_proxy.soap);

	int nRes = m_proxy.GetSystemDateAndTime(req.d, resp.d);

	CHECKRETURN(nRes, "DeviceClient::GetDateAndTime");
}


int DeviceClient::SetDateAndTime(const DevSetSystemDateAndTime & req)
{
    DevSetSystemDateAndTimeResponse resp(m_proxy.soap);

	int nRes = m_proxy.SetSystemDateAndTime(req.d, resp.d);

	CHECKRETURN(nRes, "DeviceClient::SetDateAndTime");
}
/*
int DeviceClient::GetDeviceInfo(DevGetDeviceInformationResponse & resp)
{
	DevGetDeviceInformation req(&m_proxy);

	int nRes = m_proxy.GetDeviceInformation(req.d, resp.d);

	CHECKRETURN(nRes, "DeviceClient::GetDeviceInfo");
}

int DeviceClient::GetCapabilities(DevGetCapabilitiesResponse & resp)
{
	DevGetCapabilities req(&m_proxy);

	int nRes = m_proxy.GetCapabilities(req.d, resp.d);

	CHECKRETURN(nRes, "DeviceClient::GetDeviceInfo");
}
*/

int DeviceClient::GetUsers(DevGetUsersResponse & resp)
{
	DevGetUsers req(m_proxy.soap);

	int nRes = m_proxy.GetUsers(req.d, resp.d);

	CHECKRETURN(nRes, "DeviceClient::GetUsers");
}

int DeviceClient::GetServices(DevGetServicesResponse & resp)
{
	DevGetServices req(m_proxy.soap);
	int nRes = m_proxy.GetServices(req.d, resp.d);

	CHECKRETURN(nRes, "DeviceClient::GetServices");
}
} // namespace Web
