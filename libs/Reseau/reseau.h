#ifndef _RESEAU_H


#include "dns.h"
#include "dns_etape0.h"

#define HOTE "172.26.188.11"
#define HOTE1 "193.48.57.48"
#define MAX_ADRESSE 1024

int messageUDP(char *,char *,char *,char*,int *,int*);
int initialisationSocketUDP(char *);
int boucleServeurUDP(int,int (*)(unsigned char*,int,uint8_t*,int));
int Renvoi_Client(char *,int, void*,unsigned int *);




#endif 
