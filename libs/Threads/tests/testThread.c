
#include<assert.h>

#include "thread.h"


void* fonction_test(void* arg){
	int *i=malloc(sizeof(int));
	memcpy(i,arg, sizeof(int));	
	printf("Affichage de i incrémenté: %d\n",*i+1);
	free(i);
	return NULL;
}

void test_launchThread(void *(*fonction)(void*), void *arg, size_t argSize){
	printf("Test LaunchThread, int=%d :", *((int*)arg));
	assert(launchThread(fonction,arg,argSize)==0);
	printf("Success\n");

}


int main(void){
	int* pi = malloc(sizeof(int));
       	*pi = 6;	
	fonction_test(pi);
	test_launchThread(fonction_test,(void*)pi,sizeof(int));
	return 0;
}
