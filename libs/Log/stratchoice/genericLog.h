#ifndef _GENERICLOG_H__
#define _GENERICLOG_H__

#include "../strat1/log_dns1.h"
#include<dlfcn.h>

#define STRATEGIE "nostrategie"
#define INIT_ARGS_STRATEGIE "default.txt"


int loadStrategy(char *);
int initStrategy(void *);
int logStrategy(logMsg_t *);
int close_dl(void);

#endif
