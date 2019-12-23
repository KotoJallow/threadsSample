#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>


#define SIZE 10

typedef struct segment {
		int* arr;
		int len;
	}
segment;

void* f(void * args){
	printf("Hello From Thread\n");
}

void * averager(void* arg){
	segment *sgt = (segment*) arg;
	int* arr = sgt->arr;
	int len = sgt->len;

	int i,sum = 0;
	for(i=0;i<len;i++){
		sum += *(arr+i);
	}
	double avg =  (double) sum/len;
	printf("Average from %lu is %.2f\n",pthread_self(),avg);
}

void fillArray(int* arr){
	int i;
	for(i=0;i<SIZE;i++){
		*(arr+i) = 100 + rand()%900;
	}
}
void display(int *arr){int i;for(i=0;i<SIZE;i++)printf("%d ",*(arr+i));printf("\n");}
int main(int argc,char* argv[]){
	srand(time(0));
	if(argc != 2){
		perror("Missing commandline arguments\n");
		return -1;
	}
	int len = atoi(argv[1]);
	if(!len){
		perror("Invalid argument");

		return -1;
	}
	segment* sgt = (segment*)malloc(sizeof(segment));
	int arr[SIZE];
	fillArray(arr);

	sgt->arr = arr;
	sgt->len = len;
	pthread_t thread;
	pthread_create(&thread,NULL,averager,(void*)sgt);
	pthread_join(thread,NULL);
	free(sgt);
	display(arr);
	return 0;
}
