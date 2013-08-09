#ifndef STRINGGENERATOR_H
#define STRINGGENERATOR_H

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "OnvifSDK.h"

#define TOKEN_LEN 20

static const char alphanum[] =
"0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

typedef struct GeneratorInitializer_
{ GeneratorInitializer_()
    {
        srand(time(0));
    }
} GeneratorInitializer;

static int stringLength = sizeof(alphanum) - 1;

#endif //STRINGGENERATOR_H
