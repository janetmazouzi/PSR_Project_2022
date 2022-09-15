#include <assert.h>

#include "redirection.h"

void test_initfichier(void* filename){
	printf("Test initfichier, filename =%s ",(char*) filename);
	assert(initfichier(filename)==0);
	printf("Success\n");
}


void test_add_line(char* str){
	printf("Test add_line, str=%s",str);
	assert(add_line(str)==0);
	printf("Success\n");
}


void test_add_memoire(){
	assert(add_memoire()==0);
	printf("Success\n");
}

void test_recup_adresse(char* domain_name,int type, char*c){
	printf("Test recup_adresse, domain_name = %s, type = %d", domain_name, type);
	assert(recup_adresse(domain_name, type, c)==0);
	printf("Success\n");
	}

void test_redirection_msg(char* message, int nboctet){
	printf("Test redirection_msg, message = %s, nboctet = %d", message, nboctet);
	assert(redirection_msg(message, nboctet)==0);
	printf("Success\n");
}

void test_sup_ligne(char* domain_name){
	printf("Test sup_ligne, domain_name = %s", domain_name);
	assert(sup_ligne(domain_name) ==0);
	printf("Success\n");
}

void test_modif_ligne(char* line){
	printf("Test modif_ligne, line = %s", line);
	assert(sup_ligne(line)==0);
	printf("Success\n");
}

int main(){
	return 0;
}








