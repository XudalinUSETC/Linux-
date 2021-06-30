#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>
int main(int argc,char* argv[]){

	pid_t pid=fork();
	if(pid==-1){
		perror("fork error");
		exit(1);
	}
	else if(pid==0){
		//execlp("date","date",NULL);
		execl("./process","./process",NULL);
		perror("exec,error");
		exit(1);
	}
	else if(pid>0){
		sleep(1);
		printf("I'm parent:%d\n",getpid());
	}
	return 0;
}
