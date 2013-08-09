#ifndef WSDD_LIB__H
#define WSDD_LIB__H

#include <string>
#include <vector>

class IWsdd
{
public:
    virtual int start(bool bIsDevice) = 0;
    virtual std::vector<std::string> getMembers() = 0;
    virtual int stop() = 0;
	
};

IWsdd* getWsdd(); 

#endif //WSDD_LIB__H

