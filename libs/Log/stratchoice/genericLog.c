#include"genericLog.h"

void *handle;
int loadStrategy(char *lib){
	if (dlopen(lib,RTLD_LAZY)==NULL){
		fprintf(stderr, "Error: %s\n", dlerror());
		return -1;
	}
	handle = dlopen(lib,RTLD_LAZY);
	return 0;
}

int initStrategy(void *filename){
	int (*f_init)(void *);
	f_init = dlsym(handle, "initLog");
	if (f_init==NULL) {
        	fprintf(stderr, "Error: %s\n", dlerror());
        	return -1;
	}
	else{
		if (f_init(filename)==-1){
			dlclose(handle);
			return -1;
		}
		return 0;
	}
}


int logStrategy(logMsg_t *c){
	int (*f_add)(logMsg_t *);
	f_add = dlsym(handle, "addLog");
	if (f_add==NULL) {
        	fprintf(stderr, "Error: %s\n", dlerror());
 		dlclose(handle);
        	return -1;
	}
	else{
		if (f_add(c)==-1){
			dlclose(handle);
			return -1;
		}
		return 0;
	}
	return 0;}

int close_dl(void){
	if(handle!=NULL)
		return dlclose(handle);
	return 0;
}
