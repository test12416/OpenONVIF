
#include <stdio.h>
#include "OnvifSDK.h"

int main(const int argc, const char* argv[])
{ 
    IOnvifClient * pClient = getOnvifClient();
    if(argc < 2)
    {
        printf("Input endpoint address. example:127.0.0.1:80\n");
        return -1;
    }

    pClient->Init(argv[1]);
    soap* pSoap = pClient->GetSoap();
    DevGetSystemDateAndTimeResponse r(pSoap);
    int iRet = pClient->GetDateAndTime(r);
    if(iRet != 0)
    {
        printf("GetDateAndTime failed\n");
    }
    else
    {
         int nYear, nMonth, nDay, nHour, nMin, nSec;
         r.GetUTCDateAndTime(nYear, nMonth, nDay, nHour, nMin, nSec);
         printf("DeviceService response is:\nDate is %d:%d:%d\nTime is %d:%d:%d\n", nYear, nMonth, nDay, nHour, nMin, nSec);
    }

    sleep(30);
    std::vector<std::string> devices = pClient->GetDiscoveredDevices();
    if(devices.size() == 0) {
        printf("Disappointment. 0 devices were discovered\n");
    } else {
        for(int i = 0; i < devices.size(); i++)
            printf("Discovered device: %s\n", devices[i].c_str());
    }
	
    return 0; 
}

