#include "redirection.h"

FILE* f =NULL;
int shmid;
redir_t** mem;


int initfichier(void *filename){
	f = fopen(filename,"r");
	if (f==NULL) return -1;
	return 0;
}

int nb_ligne(){
	int c = 0;
	int nligne=0;
	while((c=fgetc(f)) != EOF)
	{
		if (c == '\n')
			nligne++;
	}
	return nligne;
}

int add_line(char* str){
	redir_t *tab_mem[TAILLE_MEM];

	if((mem=(redir_t**)shmat(shmid,(void*)0,0))==(redir_t**)(-1)){
		perror("shmat");
		exit(2);
	}
	memcpy(tab_mem,mem,TAILLE_MEM*sizeof(redir_t*));
	
	int indice=0;
	while((indice<TAILLE_MEM)&&(tab_mem[indice]!=NULL)){
		indice++;
	}
	if(indice==TAILLE_MEM) return -1;

	tab_mem[indice]=malloc(sizeof(redir_t));

	char**pstr = &str;
	char*token_ini=strsep(pstr,"=");
	strcpy(tab_mem[indice]->domain_name,token_ini);

	char *adresses= malloc(100*sizeof(char));
	token_ini=strsep(pstr,"=");
	if(token_ini!=NULL)
		strcpy(adresses,token_ini);

	char **padrr = &adresses;

	char* token = strsep(padrr,",");
	int i =1;
	while(token != NULL){
		if (i==1)
			strcpy(tab_mem[indice]->addr4,token);
		if (i==2)
			strcpy(tab_mem[indice]->addr6,token);
		if (i==3){
			strcpy(tab_mem[indice]->addrMX,token);
		}
		i++;
		token = strsep(padrr,",");

		}
#ifdef DEBUG
	printf("lecture mem nouvelle ligne %s=%s,%s,%s\n",tab_mem[indice]->domain_name,tab_mem[indice]->addr4,tab_mem[indice]->addr6,tab_mem[indice]->addrMX);
#endif
	memcpy(mem,tab_mem,TAILLE_MEM*sizeof(redir_t*));
	shmdt(mem);

	return 0;
}

	

int add_memoire(){
	if ((shmid=shmget (CLE,TAILLE_MEM*sizeof(redir_t*), IPC_CREAT|IPC_EXCL|00666)) ==-1){
		perror("shmget");
		exit(2);
	}
	if((mem=(redir_t**)shmat(shmid,0,0))==(redir_t**)(-1)){
		perror("shmat");
		exit(2);
	}
	shmdt(mem);

	char str[TAILLE_MAX] ="";
	int i=0;

	while (fgets(str, TAILLE_MAX, f)!= NULL){
#ifdef DEBUG
		printf("nouvelle ligne : %s\n",str);	
#endif
		add_line(str);
		i++;
	}




	return 0;
}

int recup_adresse(char*domain_name,int type,char *c){
	redir_t *tab_mem[TAILLE_MEM];

	if((mem=(redir_t**)shmat(shmid,0,0))==(redir_t**)(-1)){
		perror("shmat");
		exit(2);
	}
	memcpy(tab_mem,mem,TAILLE_MEM*sizeof(redir_t*));

	if(type<0)return -1;
	int i=0;
	while((tab_mem[i]!=NULL)&&(i<TAILLE_MEM)&&(!strcmp(tab_mem[i]->domain_name,domain_name))){
		i++;
	}

	if(i==TAILLE_MEM) return -1;
	else {
		if (type==NUM_IPV4){
			memcpy(c,tab_mem[i]->addr4,TAILLE_STANDARD);
		}
		else if (type==NUM_IPV4)
			memcpy(c,tab_mem[i]->addr6,TAILLE_STANDARD);
		else if (type==NUM_MX){
			return -1; //car je ne sais pas quoi faire haha
		}

	}
	return 0;
}


int redirection_msg(char*message,int nboct){ //consommateur 
	uint8_t msg[nboct];
	memcpy(msg,message,nboct);
	int i=12; //Taille du header avant dns
	int k=0;
	int j;
	char domain_name[TAILLE_ADDR_DM];
	while (message[i] != 0x00)
		{
			int nb_char = message[i];
			for (j=0;j<nb_char;j++){
				domain_name[k]=message[i+j+1];
				k=k+1;
			}
			i+=nb_char+1;
			if (message[i] != 0x00){
				domain_name[k]='.';
				k = k + 1;;
			}
		}

	i=i+2;
	int type=-1,taille;
	switch(message[i])
	{
		case 0x01 : type=NUM_IPV4;
			    taille=TAILLE_ADDR_IPV4;
								break;
		case 0x1c : type=NUM_IPV6;
			    taille=TAILLE_ADDR_IPV6;
								break;
		case 0x0F : type=NUM_MX;
			    taille=TAILLE_ADDR_MX;
								break;
	}
	
	char new_adresse[TAILLE_STANDARD];
	if(type==-1) return -1;

		if(recup_adresse(domain_name,type,new_adresse)==0){
			
		memcpy(message+nboct-taille,new_adresse,sizeof(uint8_t)*taille);
		}
	return 0;

}


void free_mem(){
	redir_t *tab_mem[TAILLE_MEM];
	if((mem=(redir_t**)shmat(shmid,0,0))==(redir_t**)(-1)){
		perror("shmat");
		exit(2);
	}
	for(int i=0; i<TAILLE_MEM;i++){
		if(tab_mem[i]!=NULL) free(tab_mem[i]);
	}
	shmctl(shmid, IPC_RMID,0);
}


