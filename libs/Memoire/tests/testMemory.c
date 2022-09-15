#include<assert.h>

#include "memoire.h"

void test_allocateMemory(size_t size){
	printf("Test allocateMemory, size=%d :", (int)size);
	assert(allocateMemory(size)==0);
	printf("Success\n");

}


void test_writeMemory(void *data, uint8_t size){
	printf("Test writeMemory, size=%d :", (int)size);
	assert(writeMemory(data,size)==0);
	printf("Success\n");

}


void test_readMemory(uint8_t *size){

	printf("Test readMemory, :") ;
	assert(readMemory(size)==NULL);

	printf("Success\n");


}

int main(void){
	char s[5]="abcd";
	size_t taille_test= 256;

	//test read
	uint8_t size=0;
	test_readMemory(&size);

	test_allocateMemory(taille_test);

	//test_write
	allocateMemory(4);
	test_writeMemory((void*)s,strlen(s));

	return 0;
}
