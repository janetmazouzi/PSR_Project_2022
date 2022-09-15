#ifndef __MEMOIRE_H__
#define __MEMOIRE_H__

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<stdbool.h>
#define SIZE_BUFFER 512
//uint8_t *mem_array=NULL;

bool memoryIsEmpty(void);

int allocateMemory(size_t);

int writeMemory(void*,uint8_t);

void *readMemory(uint8_t *);

void freeMemory(void);

#endif
