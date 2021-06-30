#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main(int argc,char* argv[]){

	int fd[2];
	int ret,i;
	pid_t pid;
	ret=pipe(fd);
	if(ret==-1){
		perror("pipe error");
		exit(1);
	}
	for(i=0;i<2;i++){
		pid=fork();
		if(pid==-1){
			perror("fork error");
			exit(1);
		}
		if(pid==0){
			break;
		}
	}
	if(i==2){
		close(fd[0]);
		close(fd[1]);
		wait(NULL);
		wait(NULL);
	}else if(i==0){
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		execlp("ls","ls",NULL);
	}else if(i==1){
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		execlp("wc","wc","-l",NULL);
	}
return 0;
}
