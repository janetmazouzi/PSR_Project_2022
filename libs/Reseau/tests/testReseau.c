#include<assert.h>
#include<signal.h>

#include"reseau.h"

struct sigaction action;


int dnssock = -1;

void testmessageUDP(char *hote,char *service,char *message,char*response,int *taille_oct_rec,int*taille_oct_env){

	printf("TestmessageUDP : hote:%s, ",hote);
	printf("service:%s, ", service);
	printf("message:%s, ",message);
	printf("taille_oct:%d\n",*taille_oct_rec);
	assert(messageUDP(hote,service,message,response,taille_oct_rec,taille_oct_env)!=-1);
	printf("Success\n");
}

	

void testinitialisationSocketUDP(char *service){
	printf("TestinitialisationSocketUDP : service:%s\n",service);
	int s=initialisationSocketUDP(service);
	assert(s!=-1);
	printf("Succes, valeur de la socket : %d\n",s);
	close(s);

}
int testtraitement(unsigned char*message,int nb_oct,uint8_t *adresse,int taille_addr){
	if((message==NULL)|(nb_oct=0)|(adresse==NULL)|(taille_addr==1)) return -1;
	printf("acces à la fonction de traitement réussi\n");
	return 0;
}

void testboucleServeurUDP(int s,int (*traitement)(unsigned char*,int,uint8_t*,int)){
	printf("testboucleServeurUDP : socket:%i\n",s);
	assert(boucleServeurUDP(s,traitement)!=-1);
	printf("Succes\n");
	
}

void testRenvoi_Client(char *res,int nboctets_env, void* adresse,unsigned int *taille){
	printf("testRenvoi_Client\n");
	assert(Renvoi_Client(res,nboctets_env,adresse,taille)>-1);
	printf("succes\n");

}

void hand(int sig) {
  if (sig == SIGINT) {
#ifdef DEBUG
    printf("lib memoire\n");
#endif
    if (dnssock != -1)
	close(dnssock);

    exit(SIGINT);

  } else {
    fprintf(stderr, "erreur dans le masque de signal\n");
    exit(-1);
  }
}

int main(){
	action.sa_handler = hand;
  	sigaction(SIGINT, &action, NULL);

	testinitialisationSocketUDP(DNS_PORT);
	dnssock = initialisationSocketUDP(DNS_PORT);
	//testboucleServeurUDP(dnssock,testtraitement);

	char response[DNS_UDP_MAX_PACKET_SIZE];
	char *c="-\347\1\0\0\1\0\0\0\0\0\0\3www\6google\2fr\0\0\17\0\1";
	int nb_oct_env = strlen(c);
	int nb_oct_rec = 0;
	testmessageUDP("1.1.1.1",DNS_PORT,c,response,&nb_oct_env,&nb_oct_rec);


	struct sockaddr_storage adresse;
	socklen_t taille = sizeof(adresse);


	testRenvoi_Client(response,nb_oct_env,(void*)&adresse,(unsigned int*)&taille);	
	
	return 0;
}
