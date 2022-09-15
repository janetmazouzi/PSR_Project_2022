#ifndef __THREAD_H__
#define __THREAD_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct func_arg{
	void *fonction;
	void *arg;
};
typedef struct func_arg func_arg_t;


int launchThread(void* (*)(void*), void *,size_t);

void init_mutex(int);
void prendre(int);
void vendre(int);
void fin_thread(void);
void detach_thread(void);

#endif
