#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>
int main(int argc,char* argv[]){
	printf("before fork-1-\n");
	printf("before fork-2-\n");
	printf("before fork-3-\n");
	printf("before fork-4-\n");

	pid_t pid = fork();

	if(pid== -1){

		perror("fork error");
		exit(1);
	}
	else if(pid==0){
		printf("-----child is created,pid: %d, parent-pid: %d\n",getpid(),getppid());
	}
	else{
		printf("-----parent process: my child is%d,my pid:%d,my parent pid:%d\n",pid,getpid(),getppid());
	}
	printf("================end\n");
return 0;
}
