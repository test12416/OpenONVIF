
#include "DisplayClient.h"

namespace Web {

DisplayClient::DisplayClient(const char * pchAdress, soap * s):m_proxy(s)
{
	m_proxy.soap_endpoint = pchAdress;
}

DisplayClient::~DisplayClient()
{
	
}

int DisplayClient::GetLayout(DispGetLayout & req, DispGetLayoutResponse & resp)
{
	int nRes = m_proxy.GetLayout(req.d, resp.d);

	CHECKRETURN(nRes, "DisplayClient::GetLayout");
}

int DisplayClient::GetDisplayOptions(DispGetDisplayOptions & req, DispGetDisplayOptionsResponse & resp)
{
    int nRes = m_proxy.GetDisplayOptions(req.d, resp.d);

    CHECKRETURN(nRes, "DisplayClient::GetDisplayOptions");
}

int DisplayClient::SetLayout(DispSetLayout & req)
{
    DispSetLayoutResponse resp(m_proxy.soap);

    int nRes = m_proxy.SetLayout(req.d, resp.d);

    CHECKRETURN(nRes, "DisplayClient::SetLayout");
}

int DisplayClient::CreatePaneConfiguration(DispCreatePaneConfiguration & req, DispCreatePaneConfigurationResponse & resp)
{
    int nRes = m_proxy.CreatePaneConfiguration(req.d, resp.d);

    CHECKRETURN(nRes, "DisplayClient::CreatePaneConfiguration");
}
} // namespace Web
