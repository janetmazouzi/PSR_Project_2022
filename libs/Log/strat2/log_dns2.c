#include"log_dns2.h"
#include<string.h>
#include"dns_etape0.h"
#include"dns.h"

struct testquery{
	uint16_t id, flag;
	
};
typedef struct testquery testquery_t;


int initLog(void *i){
	if(i==NULL) return 0;

	return 0;
}



int addLog(logMsg_t *message){
	testquery_t test;

	memcpy(&(test),message->msg,sizeof(testquery_t));
	if ((test.flag & FLAG_QUERY_OR_RESPONSE) == 0x80){
		printf("Message : ");
		int i=sizeof(Dns_header);
		while (message->msg[i] != 0x00)
		{
			int nb_char = message -> msg[i];
			for (int j=0;j<nb_char;j++)
				printf("%c",message->msg[i+j+1]);
			i+=nb_char+1;
			if (message->msg[i] != 0x00)
				printf("%c",'.');

		}
		printf("\n");
	}

/*
	for (int i=0; i< message->size;i++){
		printf("%x",message->msg[i]);
	}
	*/
	return 0;

}


