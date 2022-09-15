#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "args.h"
#include "genericLog.h"
#include "memoire.h"
#include "thread.h"
#include "redirection.h"


struct sigaction action;

static int dnssock = -1;
int flag_memoire = 0;
int config_active = 0;

void printUsage(void) {
  printf("-h ou --help ; affiche ce message d'aide\n");
  printf("-p PORT ou --port=PORT : change le numéro du port d'écoute. Par "
         "défaut le port est 53\n");
  printf("-s SERVEUR ou --serveur=SERVEUR : permet de spécifier le serveur DNS "
         "à utiliser pour la résolution de nom\n");
  printf(
      "-l STRATEGIE ou --logstrategy=STRATEGIE : permet de spécifier la "
      "strategie à charger pour le logging\n  1: strategie de sauvegarde des "
      "messages du dns\n   2: strategie d'affichage du nom de domaine\n");
  printf("-i INIT_ARGS_STRATEGIE ou --initlogstrategie=INIT_ARGS_STRATEGIE : "
         "permet de spécifier les parametres d'initialisation\n");
	printf("-c CONFIG_FILE ou --config=CONFIG_FILE : "
				 "permet de specifier le fichier de configutration des redirections \n");
}

struct args_traitement {
  uint8_t adresse[MAX_ADRESSE];
  unsigned int taille;
  unsigned char message[DNS_UDP_MAX_PACKET_SIZE];
  int nboctets_rec;
};
typedef struct args_traitement args_tr_t;

void *Launch_UDP(void *func_arg) {
  // recupération des arguments
  args_tr_t *args_UDP;
  args_UDP = malloc(sizeof(args_tr_t));
  memcpy(args_UDP, func_arg, sizeof(args_tr_t));
  // free(func_arg);
  unsigned char response[DNS_UDP_MAX_PACKET_SIZE];
  int nb_oct_env = 0;

  // On doit verifier que le message est une query
  Dns_header Header = {};
  memcpy((void *)(&Header), args_UDP->message, sizeof(Dns_header));
  if ((Header.flag & FLAG_QUERY_OR_RESPONSE) == 0x00) {
    if (-1 == messageUDP(argument.server, argument.port,
                         (char *)args_UDP->message, (char *)response,
                         &(args_UDP->nboctets_rec), &(nb_oct_env)))
      return NULL;
  }
#ifdef DEBUG
  printf("ENVOI FINAL : du PROXY vers le CLIENT\n\n");
#endif
  int oct;	
  if((config_active)&&(nb_oct_env>1)){
	redirection_msg((char*)response,nb_oct_env);
  }

  oct = Renvoi_Client((char *)response, nb_oct_env, args_UDP->adresse,
                          (socklen_t *)&(args_UDP->taille));
  if (oct != nb_oct_env) {
    perror("messageUDPgenerique.sento");
    exit(EXIT_FAILURE);
  }

  // envoi vers la mémoire (partie producteur)
  prendre(0);
  writeMemory(response, (uint8_t)(nb_oct_env));
  flag_memoire = 1;
  vendre(0);

  return NULL;
}

void *Launch_Log(void *arg) {
  if (arg != NULL) {
    fprintf(stderr, "Argument du Log non vide \n");
    exit(EXIT_FAILURE);
  }
  while (1) {
    uint8_t size = 0;
    if (flag_memoire) {

      prendre(0);

      void *message = readMemory(&size);
#ifdef DEBUG
      printf("acces à read\n");
#endif
      flag_memoire = 0;
      vendre(0);
      if (size > 0) {
        logMsg_t *arg_Log = malloc(sizeof(logMsg_t) + size);

        memcpy(arg_Log->msg, message, size);
        arg_Log->size = size;

        logStrategy(arg_Log);
        free(arg_Log);
      } else
        sleep(1);
    }
  }
  return NULL;
}

int votreFonctionUDP(unsigned char *message, int nb_oct_rec, uint8_t *adresse,
                     int taille) {
  args_tr_t argstr;
  memcpy(argstr.message, message,
         sizeof(unsigned char) * DNS_UDP_MAX_PACKET_SIZE);
  memcpy(argstr.adresse, adresse, taille);
  argstr.nboctets_rec = nb_oct_rec;
  argstr.taille = taille;

  if (launchThread(Launch_UDP, (void *)&argstr, sizeof(argstr)) != 0)
    return -1;

  return 0;
}

void hand(int sig) {
  if (sig == SIGINT) {
#ifdef DEBUG
    printf("lib memoire\n");
#endif
    freeMemory();

    if (dnssock != -1)
      close(dnssock);
    fin_thread();
    close_dl();
    free_mem();

    exit(SIGINT);

  } else {
    fprintf(stderr, "erreur dans le masque de signal\n");
    exit(-1);
  }
}

int main(int argc, char *argv[]) {

  // mise en place d'une fonction d'interruption
  action.sa_handler = hand;
  sigaction(SIGINT, &action, NULL);
  // initialisation mutex
  init_mutex(0);

  if (allocateMemory(SIZE_BUFFER) < 0) {
    printf("erreur d'allocation du buffer\n");
    exit(EXIT_FAILURE);
  }

  dnssock = initialisationSocketUDP(argument.port);
  if (dnssock < 0) {
    fprintf(stderr, "Port DNS non utilisable\n");
    exit(EXIT_FAILURE);
  }

  analyseArguments(argc, argv);
  if(strcmp(argument.config,"noconfig")!=0){
  	initfichier(argument.config);
	config_active=1;
	add_memoire();
  }

  if (argument.help) {
    printUsage();
    exit(EXIT_SUCCESS);
  }

  if (strcmp(argument.strategie, "nostrategie") != 0) {

    if (loadStrategy(argument.strategie) == -1) {
      fprintf(stderr, "Erreur chargement strategie \n");
      exit(EXIT_FAILURE);
    }

    if (initStrategy(argument.args_strat) == -1) {
      fprintf(stderr, "Erreur init strategie \n");
      exit(EXIT_FAILURE);
    }

    launchThread(Launch_Log, NULL, 0);
  }
  if (boucleServeurUDP(dnssock, votreFonctionUDP) < 0) {
    fprintf(stderr, "Erreur dans le proxy DNS \n");
    exit(EXIT_FAILURE);
  }

  freeMemory();

  if (dnssock != -1)
    close(dnssock);
  close_dl();

  return 0;
}
