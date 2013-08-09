
#include "OnvifSDK.h"
#include "OnvifTestServer.h"

int main()
{
    IOnvifServer * srv = getOnvifServer();
	
    OnvifTestServer handler; 
    int iRet = srv->Init(DEV_S, 8080, &handler);
    if(iRet != 0)
	    return -1;
    if(srv->Run() != 0)
        return -1;

    return 0;
}
