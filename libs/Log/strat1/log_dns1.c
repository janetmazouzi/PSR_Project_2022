#include"log_dns1.h"


FILE * f = NULL;


int initLog(void *filename){
	f = fopen(filename, "w");
	printf("fichier : %p\n",f);
	if (f==NULL) return -1;
	return 0;
}


int addLog(logMsg_t *message){
	for (int i=0; i< message->size;i++){
		fprintf(f, "%x",message->msg[i]);
	}
	fprintf(f,"\n");
	fflush(f);
	//fclose(f);
	return 0;

}


