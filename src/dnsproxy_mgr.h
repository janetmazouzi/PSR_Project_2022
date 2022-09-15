
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdint.h>

#define CONFIG_FILE "src/config_file.txt"

#define TAILLE_MEM 50
#define TAILLE_MAX 1000
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


#define NEWLINE "\0"
#define DOMAIN_NAME "\0"
#define MODIFLINE "\0"

typedef struct args_s {
	bool help;
	char ajout[TAILLE_MAX];
	char suppression[TAILLE_ADDR_DM];
	char modification[TAILLE_MAX];
} args_t;



