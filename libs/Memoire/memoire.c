#include"memoire.h"

static size_t write_ind=0;
static size_t read_ind=0;
static size_t mem_size=0;
static size_t buffer_size=0;
uint8_t *mem_array=NULL;


bool memoryIsEmpty(void){
	return mem_array==NULL;
}

int allocateMemory(size_t size){
	mem_size=size;
	mem_array=malloc(size);
	if (mem_array == NULL) return -1;
	return 0;


}

int writeMemory(void *data ,uint8_t size){
	#ifdef DEBUG
	printf("ECRITURE DANS LE BUFFER\n");
	printf("size %d\n",size);
	#endif
	if(mem_size-buffer_size<size) return -1;
	mem_array[write_ind]=size;
	if(mem_size-write_ind < size){   //cas où on n'écrase pas d'ancienne données (on ne passe pas par la case 0 du tableau)
		memcpy(mem_array+write_ind+1, data,size);
		write_ind+=size;
	}
	else {                      //cas où on écrase les anciennes données
		for (int i=0;i<size;i++){
			if (write_ind<mem_size){
				write_ind++;
				memcpy(mem_array+write_ind,data+i,1); //on écrit les données octet par octet
			}
			else{
				write_ind = 0;  //on reboucle au début du buffer circulaire
				memcpy(mem_array+write_ind,data+i,1);

			}
		}
	}
	buffer_size+=size+1;
	return 0;
}

void *readMemory(uint8_t *size){
#ifdef DEBUG
	printf("LECTURE DU BUFFER\n");
#endif
	if(buffer_size==0){
#ifdef DEBUG
		printf("Buffer vide\n");
#endif
		return NULL;}
	memcpy(size,mem_array+read_ind, sizeof(uint8_t));
	void *message=malloc((*size));
	if(read_ind+mem_array[read_ind] < mem_size){
		memcpy(message,mem_array+read_ind+1,*size);
		read_ind+=(int)*size;
	}
	else{
		for (int i=0;i<	(*size);i++){
			if (read_ind < mem_size){
				read_ind++;
				memcpy(message+i,mem_array+read_ind,1);
			}
			else{
				read_ind = 0;
				memcpy(message+i,mem_array+read_ind,1);
			}
		}
	}
	buffer_size-=(int)*size+1;
	return message;
}

void freeMemory(void){
	if(mem_array!=NULL)
		free(mem_array);
}




