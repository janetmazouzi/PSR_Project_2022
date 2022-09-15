#include "reseau.h"

int sock_cli;



int messageUDP(char *hote,char *service, char *message,char *response,int *taille_oct_rec, int* taille_oct_env){


	//création d'un deuxième traitement, on prend le message récu par le 
	//proxy, pour le renvoyer vers un DNS
	


	struct addrinfo precisions,*resultat,*origine;
	int statut;
	int s;

	/* Creation de l'adresse de socket */
	memset(&precisions,0,sizeof precisions);
	precisions.ai_family=AF_UNSPEC;
	precisions.ai_socktype=SOCK_DGRAM;
	statut=getaddrinfo(hote,service,&precisions,&origine);
	if(statut<0){ perror("messageUDPgenerique.getaddrinfo"); exit(EXIT_FAILURE); }
	struct addrinfo *p;
	for(p=origine,resultat=origine;p!=NULL;p=p->ai_next)
	if(p->ai_family==AF_INET6){ resultat=p; break; }

	/* Creation d'une socket */
	s=socket(resultat->ai_family,resultat->ai_socktype,resultat->ai_protocol);
	if(s<0){ perror("messageUDPgenerique.socket"); exit(EXIT_FAILURE); }

	/* Option sur la socket */
	int vrai=1;
	if(setsockopt(s,SOL_SOCKET,SO_BROADCAST,&vrai,sizeof(vrai))<0){
	  perror("initialisationServeurUDPgenerique.setsockopt (BROADCAST)");
	  exit(-1);
	  }

	/* Envoi du message vers le DNS*/
#ifdef DEBUG
	printf("PREMIER ENVOI : du PROXY vers le DNS\n\n");
#endif
	int nboctets=sendto(s,message,*taille_oct_rec,0,resultat->ai_addr,resultat->ai_addrlen);
	if(nboctets<0){ perror("messageUDPgenerique.sento"); exit(EXIT_FAILURE); }

	/* Liberation de la structure d'informations */
	freeaddrinfo(origine);
	struct sockaddr_storage adresse;
	socklen_t taille=sizeof(adresse);


	/* Reception du message réponse du DNS et stockage dans la var message, taille_oct prend la taille du message
	 * pour favoriser le renvoi final*/
#ifdef DEBUG
	printf("DEUXIEME RECEPTION : du DNS vers le PROXY\n\n");
#endif
	*taille_oct_env=recvfrom(s,response,DNS_UDP_MAX_PACKET_SIZE,0,(struct sockaddr *)&adresse,&taille);
	if(*taille_oct_env<0) return -1;
	/* Fermeture de la socket d'envoi */
	close(s);
	return 0;
}

int initialisationSocketUDP(char *service){
	struct addrinfo precisions,*resultat,*origine;
	int statut;
	int s;

	/* Construction de la structure adresse */
	memset(&precisions,0,sizeof precisions);
	precisions.ai_family=AF_UNSPEC;
	precisions.ai_socktype=SOCK_DGRAM;
	precisions.ai_flags=AI_PASSIVE;
	statut=getaddrinfo(NULL,service,&precisions,&origine);
	if(statut<0){ perror("initialisationSocketUDP.getaddrinfo"); exit(EXIT_FAILURE); }
	struct addrinfo *p;
	for(p=origine,resultat=origine;p!=NULL;p=p->ai_next)
	if(p->ai_family==AF_INET6){ resultat=p; break; }

	/* Creation d'une socket */
	s=socket(resultat->ai_family,resultat->ai_socktype,resultat->ai_protocol);
	if(s<0){ perror("initialisationSocketUDP.socket"); exit(EXIT_FAILURE); }

/* Options utiles 
	int vrai=1;
	if(setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&vrai,sizeof(vrai))<0){
	       	perror("initialisationServeurUDPgenerique.setsockopt (REUSEADDR)");
		exit(-1);
	  }
*/
/* Specification de l'adresse de la socket */
	statut=bind(s,resultat->ai_addr,resultat->ai_addrlen);
	if(statut<0) {perror("initialisationServeurUDP.bind"); exit(-1);}

/* Liberation de la structure d'informations */
	freeaddrinfo(origine);

	return s;
}

int boucleServeurUDP(int s,int (*traitement)(unsigned char*,int,uint8_t*,int)){
	sock_cli = s;
	unsigned char message[DNS_UDP_MAX_PACKET_SIZE];
	while(1){ 

		struct sockaddr_storage adresse;
		socklen_t taille = sizeof(adresse);

		//PREMIERE ACTION : le proxy attend la reception d'un message, stocké dans la var message
#ifdef DEBUG
		printf("PREMIERE RECEPTION : du client vers le proxy\n\n");
#endif
		int nboctets_rec=recvfrom(sock_cli,message,DNS_UDP_MAX_PACKET_SIZE,0,(struct sockaddr *)&adresse,&taille);
		if(nboctets_rec<0) return -1;
		

		traitement((unsigned char*)message,nboctets_rec,(uint8_t*)&adresse,(int)taille);



	}
	return 0;
}
int Renvoi_Client(char *res,int nboctets_env, void* adresse,unsigned int *taille){
	return sendto(sock_cli,res,nboctets_env,0,(struct sockaddr *)(adresse),*taille);

}


