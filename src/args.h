#ifndef __ARGS_H__
#define __ARGS_H__

#include <stdbool.h>
#include"../libs/Reseau/reseau.h"

#define MAX_PORT_SIZE	8
#define MAX_SERVICE_SIZE	256
#define MAX_STRAT_SIZE	100
#define MAX_INIT_STRAT_SIZE	100
#define MAX_CONFIG_FILE 100

typedef struct args_s {
	bool help;
	char port[MAX_PORT_SIZE];
	char server[MAX_SERVICE_SIZE];
	char strategie[MAX_STRAT_SIZE];
	char args_strat[MAX_INIT_STRAT_SIZE];
	char config[MAX_CONFIG_FILE];
} args_t;

extern args_t argument;

void analyseArguments(int argc, char *argv[]);

#endif
