#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include"args.h"
#include"genericLog.h"
#include"redirection.h"

args_t argument = { .help = false,
	.port = DNS_PORT,
	.server = HOTE,
	.strategie = STRATEGIE, 
	.args_strat = INIT_ARGS_STRATEGIE,
	.config = CONFIG_FILE
};

void analyseArguments(int argc, char *argv[])
{
	int c;

	static struct option long_options[] = 
	{
		{"help", 		no_argument, 		0, 'h'},
		{"port", 		required_argument, 	0, 'p'},
		{"serveur", 		required_argument, 	0, 's'},
		{"logstrategy", 	required_argument, 	0, 'l'},
		{"initlogstrategy", 	required_argument, 	0, 'i'},
		{"config", 	required_argument, 	0, 'c'},
		{0, 0, 0, 0}
	};

	while(1)
	{
		int option_index = 0;
		c = getopt_long(argc, argv, "hp:s:l:i:c:", long_options, &option_index);
		if(c == -1)
			break;

		switch(c)
		{
			case 'h': argument.help = true;
					  break;
			case 'p': if(strlen(optarg)<(MAX_PORT_SIZE-1))
						  strcpy(argument.port, optarg);
					  else
					  {
						  strncpy(argument.port, optarg, MAX_PORT_SIZE-1);
						  argument.port[MAX_PORT_SIZE-1] = '\0';
					  }
					  break;
			case 's' : if(strlen(optarg)<(MAX_SERVICE_SIZE-1))
						  strcpy(argument.server, optarg);
				   else
				   {
					   strncpy(argument.server, optarg, MAX_SERVICE_SIZE-1);
					   argument.server[MAX_SERVICE_SIZE-1] = '\0';
				   }
				   break;
			case 'l' : if(strlen(optarg)<2){
					   if(!strcmp("1",optarg)){

					   	strcpy(argument.strategie, "liblog_dns1.so.1.0");
					   }
					   else if (!strcmp("2", optarg))
					   	strcpy(argument.strategie, "liblog_dns2.so.1.0");
					   else
					   	strcpy(argument.strategie, "nostrategie");
				   }else{
					   strncpy(argument.strategie, optarg, MAX_STRAT_SIZE-1);
					   argument.strategie[MAX_STRAT_SIZE-1] = '\0';
				   }
				   break;
			case 'i' : if(strlen(optarg)<MAX_INIT_STRAT_SIZE)
					   strcpy(argument.args_strat, optarg);
				   else{
					   strncpy(argument.args_strat, optarg, MAX_INIT_STRAT_SIZE-1);
					   argument.args_strat[MAX_INIT_STRAT_SIZE-1] = '\0';
				   }
					 break;
			case 'c' : if(strlen(optarg)<MAX_CONFIG_FILE){
					   strcpy(argument.config, optarg);
				   }else{
					   strncpy(argument.config, optarg, MAX_CONFIG_FILE-1);
					   argument.args_strat[MAX_CONFIG_FILE-1] = '\0';
				   }

				   break;
		}
	}
}

