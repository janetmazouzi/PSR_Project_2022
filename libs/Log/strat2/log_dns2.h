#ifndef __LOG_DNS_H__
#define __LOG_DNS_H__

#include<stdio.h>
#include<stdlib.h>

typedef struct logMsg_s {
	int size;
	char msg[1];
} logMsg_t;

int initLog(void *);
int addLog(logMsg_t *);

#endif
