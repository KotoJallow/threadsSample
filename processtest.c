#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	pid_t pid, pid1;
	pid = fork();
	if(pid==0){
		printf("Process successfully created: %d\n",getpid());
	}else if(pid > 0){
		printf("Parent is runnig: %d\n",getpid());
	}else{
		fprintf(stderr,"Error in creating process\n");
	}
	pid1 = fork();
	if(pid1==0) printf("New Child is created %d\n",getpid());
}
