
#include <stdio.h>
#include "sigrlog.h"
#include "OnvifTestServer.h"

int OnvifTestServer::GetDateAndTime(DevGetSystemDateAndTimeResponse & dt) 
{
    time_t t = time(0);
    struct tm * now = localtime( & t );

    if(now == NULL)
    {
        SIGRLOG(SIGRWARNING, "OnvifTestServer::GetDateAndTime Getting localtime failed");
        return -1;
    }

    dt.SetUTCDateAndTime(now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);

    return 0;
}

