
#include "sigrlog.h"
#include "DeviceIOServiceImpl.h"
#include "BaseServer.h"

namespace Web {
#warning TODO for while not supporting copy
DeviceIOBindingService* DeviceIOServiceImpl::copy()
{
	return NULL;
}

int DeviceIOServiceImpl::GetVideoOutputs(_tmd__GetVideoOutputs *tmd__GetVideoOutputs, _tmd__GetVideoOutputsResponse *tmd__GetVideoOutputsResponse)
{
    DevIOGetVideoOutputsResponse resp(tmd__GetVideoOutputsResponse);

    int nRes = m_pBaseServer->GetVideoOutputs(resp);

    CHECKRETURN(nRes, "DeviceIOServiceImpl::GetVideoOutputs");
}
} // namespace Web
