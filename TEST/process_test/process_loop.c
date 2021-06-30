#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>
int main(int argc,char* argv[]){

	int i;
	pid_t pid;
	for(i=0;i<5;i++){
		pid=fork();
		if(pid==0){
			break;
		}
	}
	if(i==5){
		sleep(5);
		printf("I'm parent\n'");
	}
	else{
		sleep(i);
		printf("I'm %dth child\n",i+1);
	}
return 0;
}
