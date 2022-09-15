#ifndef __REDIRECTION_H__
#define __REDIRECTION_H__

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<stdlib.h>
#include<stdint.h>

#define CONFIG_FILE "src/config_file.txt"

#define TAILLE_MEM 50
#define TAILLE_MAX 1000
#define CLE (key_t)100
#define TAILLE_STANDARD 40
#define TAILLE_ADDR_DM 40
#define TAILLE_ADDR_IPV4 4
#define TAILLE_ADDR_IPV6 16
#define TAILLE_ADDR_MX 4

#define NUM_IPV4 1
#define NUM_IPV6 2
#define NUM_MX 3


struct redir_s{
	char domain_name[TAILLE_ADDR_DM];
	char addr4[TAILLE_STANDARD];
	char addr6[TAILLE_STANDARD];
	char addrMX[TAILLE_STANDARD];
};
typedef struct redir_s redir_t;

int initfichier(void*);
int nb_ligne(void);
int add_line(char*);
int add_memoire(void);
int recup_adresse(char*,int,char*);
int redirection_msg(char*,int);
void free_mem(void);



#endif
