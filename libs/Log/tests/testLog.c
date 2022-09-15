#include<stdio.h>
#include<string.h>
#include<assert.h>

#include "genericLog.h"


void test_loadStrategy(char * lib){
	printf("Test loadStrategy, lib = %s", lib);
	assert(loadStrategy(lib)==0);
	printf("Success\n");
}


void test_initStrategy(void *filename){
	printf("Test initStrategy");
	assert(initStrategy(filename)==0);
	printf("Success\n");
}

void test_logStrategy(logMsg_t* c){
	printf("Test logStrategy");
	assert(logStrategy(c)==0);
	printf("Success\n");
}

void test_close_dl(void){
	printf("Test close_dl");
	assert(close_dl()==0);
	printf("Success\n");

}

int main(void){
	char* test = "liblog_dns2.so";
	test_loadStrategy(test);
	char* empty = "default.txt";

	char *msg = ",\347\201\200\0\1\0\1\0\0\0\0\3www\6google\2fr\0\0\34\0\1\300";

	int j = initStrategy((void*)empty);
	printf("j = %d", j);
	test_initStrategy(empty);

	logMsg_t* ptr_struct = malloc(sizeof(logMsg_t)+strlen(msg));
	ptr_struct -> size = strlen(msg);

	memcpy(ptr_struct -> msg,msg,ptr_struct->size);
	test_logStrategy(ptr_struct);

	free(ptr_struct);
	test_close_dl();
	return 0;
}



