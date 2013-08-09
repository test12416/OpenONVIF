#ifndef COMMONTYPES_H
#define COMMONTYPES_H

//** for allocation of the internal objects redefine EXTRA_CONSTRUCT()
#define CLASS_CTORS(gSoapPrefix, servicePrefix, classname)\
    servicePrefix ## classname::servicePrefix ## classname ( _ ## gSoapPrefix ## __ ## classname * pData)\
    {\
        this->d = pData;\
        EXTRA_CONSTRUCT()\
    };\
\
	servicePrefix ## classname::servicePrefix ## classname ( soap * pSoap )\
	{\
		this->d = soap_new__ ## gSoapPrefix ## __ ## classname (pSoap);\
		EXTRA_CONSTRUCT()\
	};

#endif //COMMONTYPES_H
