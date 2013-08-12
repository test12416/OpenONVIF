
#include "WsddLib.h"
#include "wsdd.hpp"

IWsdd * getWsdd()
{
    return Wsdd::Wsdd::Instance();
}
