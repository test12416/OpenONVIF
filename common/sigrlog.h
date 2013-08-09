
#ifndef SIGRLOG_H
#define SIGRLOG_H

#include "stdio.h"

//======================================================

// need to set
//
//  SIGRLOG_CURRLEVEL		[0;4]
//  SIGRLOG_OUTPUT			[1;3]
//  SIGRLOG_FILENAME        "filename"

//======================================================

typedef enum _SigrLogLevel
{
	SIGRCRITICAL = 0,
	SIGRWARNING = 1,
	SIGRDEBUG0 = 2,
	SIGRDEBUG1 = 3,
	SIGRDEBUG2 = 4,
	SIGREND
} SiglLogLevel;

static const char * loglevel [SIGREND] = {"CRITICAL", "WARNING", "DEBUG0","DEBUG1","DEBUG2"};

#define SIGRLOG_CONSOLE		0x01
#define SIGRLOG_LOGFILE		0x02

#define SIGRLOG(level, fmt...)\
    do {\
    	if(level <= SIGRLOG_CURRLEVEL && level < SIGREND)\
    	{\
    		if(SIGRLOG_OUTPUT & SIGRLOG_CONSOLE)\
    		{\
				printf("SIGRLOG[%s]: ", loglevel[level]);\
				printf(fmt);\
				printf("\n");\
    		}\
    		if(SIGRLOG_OUTPUT & SIGRLOG_LOGFILE)\
    		{\
    			FILE * fp;\
    			fp = fopen(SIGRLOG_FILENAME,"a+");\
    			if(fp)\
    			{\
    				fprintf(fp, "SIGRLOG[%s]: ", loglevel[level]);\
    				fprintf(fp, fmt);\
    				fprintf(fp, "\n");\
    			}\
    			fclose(fp);\
    		}\
    	}\
    }while(0) 

#define CHECKRETURN(nRes, str) \
    do{\
    if(nRes != 0) \
    {\
        SIGRLOG(SIGRWARNING, "%s failed!", str);\
        return -1;\
    }\
    else\
    {\
        SIGRLOG(SIGRDEBUG2, "%s suceeded!", str);\
        return 0;\
    }\
    }while(0)
    

#endif // SIGRLOG_H
