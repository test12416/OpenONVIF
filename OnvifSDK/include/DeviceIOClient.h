#ifndef DEVICEIOCLIENT_H
#define DEVICEIOCLIENT_H

#include "sigrlog.h"
#include "OnvifSDK.h"
#include "WebDeviceIOBindingProxy.h"

namespace Web {
class DeviceIOClient
{
public:
	DeviceIOClient(const char * pchAdress, soap * s);
	~DeviceIOClient();

	int GetVideoOutputs(DevIOGetVideoOutputsResponse &);

private:
	DeviceIOBindingProxy m_proxy;
};
} // namespace Web
#endif	// DEVICEIOCLIENT_H
