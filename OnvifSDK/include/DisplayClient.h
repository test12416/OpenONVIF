#ifndef DISPLAYCLIENT_H
#define DISPLAYCLIENT_H

#include "sigrlog.h"
#include "OnvifSDK.h"
#include "WebDisplayBindingProxy.h"

namespace Web {

class DisplayClient
{
public:
	DisplayClient(const char * pchAdress, soap * s);
	~DisplayClient();

	int GetLayout(DispGetLayout &, DispGetLayoutResponse &);
    int GetDisplayOptions(DispGetDisplayOptions &, DispGetDisplayOptionsResponse &);
    int SetLayout(DispSetLayout &);
    int CreatePaneConfiguration(DispCreatePaneConfiguration &, DispCreatePaneConfigurationResponse &);

private:
	DisplayBindingProxy m_proxy;
};
} // namespace Web
#endif	// DISPLAYCLIENT_H

