
#define CLE (key_t)100
#include "dnsproxy_mgr.h"

FILE* f =NULL;
int shmid;
redir_t** mem;
key_t key;


args_t argument = { .help = false,
	.ajout = NEWLINE,
	.suppression = DOMAIN_NAME,
	.modification = MODIFLINE
};

void printUsage(void) {
  printf("-h ou --help ; affiche ce message d'aide\n");
  printf("-a NEWLINE ou --ajout=NEWLINE : permet d'ajouter la ligne"
		 	"	à la mémoire partagée\n"
      "Le format à respecter est le suivant : domain_name=ipv4,ipv6,MX\n");
  printf("-s DOMAIN_NAME ou --suppression=DOMAIN_NAME : permet de "
			"spécifier le nom de domaine à supprimer des spécifications\n ");
  printf("-m LINE ou --modification=LINE :"
	 		"	permet de spécifier le domaine à modifier "
      "Le format à respecter est le suivant : domain_name=ipv4,ipv6,MX\n"
      "Mettre le champ à 0 si vous ne voulez pas le modifier\n");
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




int sup_ligne(char *domain_name){
	redir_t *tab_mem[TAILLE_MEM];

	if((mem=(redir_t**)shmat(shmid,0,0))==(redir_t**)(-1)){
		perror("shmat");
		exit(2);
	}
	memcpy(tab_mem,mem,TAILLE_MEM*sizeof(redir_t*));
	int i=0;
	while((i<TAILLE_MEM)&&((tab_mem[i]!=NULL)&&(!strcmp(domain_name, tab_mem[i]->domain_name)))){
		if((tab_mem[i]!=NULL)&&(!strcmp(domain_name, tab_mem[i]->domain_name))){
			free(tab_mem[i]);
			tab_mem[i] = NULL;
		}	
	}	
	if(i==TAILLE_MAX)return -1;
	memcpy(mem,tab_mem,TAILLE_MEM*sizeof(redir_t*));
	printf("ajout de %s\n",tab_mem[i]->domain_name);	
	shmdt(mem);
	return 0;
}

int modif_ligne(char *line){
	redir_t *tab_mem[TAILLE_MEM];
	redir_t modif;

	char**pline = &line;
	char*token_ini=strsep(pline,"=");
	strcpy(modif.domain_name,token_ini);

	if((mem=(redir_t**)shmat(shmid,0,0))==(redir_t**)(-1)){
		perror("shmat");
		exit(2);
	}
	memcpy(tab_mem,mem,TAILLE_MEM*sizeof(redir_t*));
	
	int indice=0;
	while((indice<TAILLE_MEM)&&(!((tab_mem[indice]!=NULL)&&(!strcmp(tab_mem[indice]->domain_name,modif.domain_name))))){
		indice++;
	}
	if(indice==TAILLE_MEM) {
		printf("nom de dommaine non-existant\n");
		return -1;
	}

	char *adresses= malloc(100*sizeof(char));
	token_ini=strsep(pline,"=");
	if(token_ini!=NULL)
		strcpy(adresses,token_ini);

	char **padrr = &adresses;

	char* token = strsep(padrr,",");
	int i =0;
	while(token != NULL){
		if (i==0){
			strcpy(modif.addr4,token);
			if(!strcmp(modif.addr4,"\0"))
				strcpy(tab_mem[indice]->addr4,modif.addr4);
		}
		if (i==1){
			strcpy(modif.addr6,token);
			if(strcmp(modif.addr6,"\0"))
				strcpy(tab_mem[indice]->addr6,modif.addr6);
		}

		if (i==2){
			strcpy(modif.addrMX,token);
			if(!strcmp(modif.addrMX,"\0"))
				strcpy(tab_mem[indice]->addrMX,modif.addrMX);
		}
		i++;
		token = strsep(padrr,",");

		}
	printf("modification de %s\n",tab_mem[i]->domain_name);	
	memcpy(mem,tab_mem,TAILLE_MEM*sizeof(redir_t*));

	shmdt(mem);

	return 0;

	
}




void analyseArguments(int argc, char *argv[])
{
	int c;

	static struct option long_options[] = 
	{
		{"help", 		no_argument, 		0, 'h'},
		{"ajout", 		required_argument, 	0, 'a'},
		{"suppression", 		required_argument, 	0, 's'},
		{"modification", 	required_argument, 	0, 'm'},
		{0, 0, 0, 0}
	};

	while(1)
	{
		int option_index = 0;
		c = getopt_long(argc, argv, "ha:s:m:", long_options, &option_index);
		if(c == -1)
			break;

		switch(c)
		{
			case 'h': argument.help = true;
					printUsage();

					  break;
			case 'a': if(strlen(optarg)<(TAILLE_MAX-1))
						  strcpy(argument.ajout, optarg);
					  else
					  {
						  strncpy(argument.ajout, optarg, TAILLE_MAX-1);
						  argument.ajout[TAILLE_MAX-1] = '\0';

					  }

					  add_line(argument.ajout);
					  break;
			case 's' : if(strlen(optarg)<(TAILLE_ADDR_DM-1))
						  strcpy(argument.suppression, optarg);
				   else
				   {
					   strncpy(argument.suppression, optarg, TAILLE_ADDR_DM-1);
					   argument.suppression[TAILLE_ADDR_DM-1] = '\0';
				   }
				   sup_ligne(argument.suppression);
				   break;
			case 'm' : if(strlen(optarg)<TAILLE_MAX)
					   strcpy(argument.modification, optarg);
				   else{
					   strncpy(argument.modification, optarg, TAILLE_MAX-1);
					   argument.modification[TAILLE_MAX-1] = '\0';
				   }
				   modif_ligne(argument.modification);
					 break;
		}
	}
}
int main(int argc, char *argv[]){
	key=ftok("shmfile",65);
	if ((shmid=shmget (key,TAILLE_MEM*sizeof(redir_t*), IPC_CREAT|IPC_EXCL|00666)) ==-1){
		perror("shmget");
		exit(2);
	}
	if((mem=(redir_t**)shmat(shmid,0,0))==(redir_t**)(-1)){
		perror("shmat");
		exit(2);
	}


	if(argument.help){
		printUsage();
		return 0;
	}
	analyseArguments(argc,argv);
	shmctl(shmid, IPC_RMID,0);
	return 0;
}

