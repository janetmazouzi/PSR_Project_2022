#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<unistd.h>




struct dns_header{
	uint16_t id;
	uint16_t flag;
	uint16_t QDcount;
	uint16_t ANcount;
	uint16_t NScount;
	uint16_t ARcount;
};

typedef struct dns_header Dns_header;



/*

void init_header(Dns_header* h){
	h -> id = 1;
	h -> flag = 0;
	h -> QDcount = 1;
	h -> ANcount =0;
	h -> NScount =0;
	h -> ARcount =0;
}

*/
