#include<pthread.h>
#include"thread.h"

#define NB_MUTEX 2
pthread_mutex_t verrou[NB_MUTEX];
pthread_t tid;



int launchThread(void *(*fonction)(void*), void *arg,size_t argSize){
	pthread_t tid1;
	

	func_arg_t *func_arg = malloc(sizeof(func_arg_t));
	func_arg->fonction=fonction;
	if(arg == NULL){
		func_arg->arg=NULL;
	}
	else{
		func_arg->arg=malloc(argSize);
		memcpy(func_arg->arg,arg,argSize);
	}
#ifdef DEBUG
	printf("avant create\n");
#endif
	int i = pthread_create(&tid1,NULL, func_arg-> fonction, func_arg ->arg);
	if(i!=0)return-1;
#ifdef DEBUG
	printf("ret value of pthread_create : %d\n", i);
	printf("après create\n");
#endif

	pthread_detach(tid1);
	free(func_arg);	
	return 0;
}

void init_mutex(int ind_mut){
	pthread_mutex_init(&(verrou[ind_mut]),NULL);
}


void prendre(int ind_mut){
	pthread_mutex_lock(&(verrou[ind_mut]));
}

void vendre(int ind_mut){
	pthread_mutex_unlock(&(verrou[ind_mut]));
}

void fin_thread(){
	pthread_exit(NULL);
}

void detach_thread(void ){
	pthread_detach(tid);
}

