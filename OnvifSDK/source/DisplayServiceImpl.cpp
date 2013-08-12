#include "sigrlog.h"
#include "DisplayServiceImpl.h"
#include "BaseServer.h"

namespace Web {
DisplayBindingService *DisplayServiceImpl::copy()
{
	return NULL;
};

int DisplayServiceImpl::GetLayout(_tls__GetLayout *tls__GetLayout, _tls__GetLayoutResponse *tls__GetLayoutResponse)
{

	DispGetLayout req(tls__GetLayout);
	DispGetLayoutResponse resp(tls__GetLayoutResponse);

	std::string requestedLayoutToken;
	req.GetLayout(requestedLayoutToken);

	
    int iRet = m_pBaseServer->GetLayout(requestedLayoutToken, resp);


	CHECKRETURN(iRet, "DisplayServiceImpl::GetLayout");
};

int DisplayServiceImpl::GetDisplayOptions(_tls__GetDisplayOptions *tls__GetDisplayOptions, _tls__GetDisplayOptionsResponse *tls__GetDisplayOptionsResponse)
{
	DispGetDisplayOptions req(tls__GetDisplayOptions);
    DispGetDisplayOptionsResponse resp(tls__GetDisplayOptionsResponse);

	std::string VOToken;
	req.GetVO(VOToken);

    int iRet = m_pBaseServer->GetDisplayOptions(VOToken, resp);

	CHECKRETURN(iRet, "DisplayServiceImpl::GetDisplayOptions");
}

int DisplayServiceImpl::SetLayout(_tls__SetLayout *tls__SetLayout, _tls__SetLayoutResponse *tls__SetLayoutResponse)
{
    DispSetLayout req(tls__SetLayout);

    int iRet = m_pBaseServer->SetLayout(req);

    CHECKRETURN(iRet, "DisplayServiceImpl::SetLayout");
}

int DisplayServiceImpl::CreatePaneConfiguration(_tls__CreatePaneConfiguration *tls__CreatePaneConfiguration, _tls__CreatePaneConfigurationResponse *tls__CreatePaneConfigurationResponse)
{
    DispCreatePaneConfiguration req(tls__CreatePaneConfiguration);
    DispCreatePaneConfigurationResponse resp(tls__CreatePaneConfigurationResponse);

    int iRet = m_pBaseServer->CreatePaneConfiguration(req, resp);

       // FIXME NO RESP SETTING
    CHECKRETURN(iRet, "DisplayServiceImpl::CreatePaneConfiguration");
}
} // namespace Web
