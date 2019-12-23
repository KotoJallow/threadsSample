#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define SIZE 1000

typedef struct segment {
		int* arr;
		int len;
		int offset;
		double *results;
	}
segment;

void * averager(void* arg){
	segment *sgt = (segment*) arg;
	int* arr = sgt->arr;
	int len = sgt->len;
	int offset = sgt->offset;

	int i,sum = 0;
	for(i=0;i<len;++i){
		sum += *(arr+i+offset);
	}
	double avg =  (double) sum/len;
	
	*(sgt->results) = avg;
	printf("Average from %lu is %.2f\n",pthread_self(),avg);
}

void fillArray(int* arr){
	int i;
	for(i=0;i<SIZE;++i){
		*(arr+i) = 100 + rand()%900;
	}
}
double mainAverage(double *arr,int len){
	int i,sum = 0;
	for(i=0;i<len;++i) sum+=arr[i];
	return (double) sum/len;
}
void allocateMemToSegment(segment *seg[],int len){
	int i;
	for(i=0;i<len;++i) seg[i] = (segment*) malloc(sizeof(segment));
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
	segment* sgt[len+1];
	int i, arr[SIZE];
	pthread_t thread[len+1];
	double results[len];
	fillArray(arr);
	//display(arr);
	allocateMemToSegment(sgt,len+1);

	int segLen = SIZE/len;
	int remainder = SIZE%len;

	for(i=0;i<len;++i){
		sgt[i]->arr = arr;
		sgt[i]->len = segLen;
		sgt[i]->offset = (i+1 == len) ? i*len + remainder : i*len; //get the offset of the next thread
		sgt[i]->results = &results[i];
		pthread_create(&thread[i],NULL,averager,(void*)sgt[i]);
	}
	for(i=0;i<len;++i)
		pthread_join(thread[i],NULL);
	for(i=0;i<len;i++) printf("Koto: %.2f\n",results[i]);
	double avg = mainAverage(results,len);
	printf("Average is %.2f",avg);	
	free(sgt);
	return 0;
}
