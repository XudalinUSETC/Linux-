#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<signal.h>
#include<sys/socket.h>
#include<arpa/inet.h>
void sys_err(const char*str){
	perror(str);
	exit(1);
}
void sig_catch(int signo){
	printf("catch you!%d\n",signo);
	return;
}
int main(int argc,char* argv[]){
	struct sigaction act,oldaction;
	act.sa_handler = sig_catch;
	sigemptyset(&(act.sa_mask));
	act.sa_flags = 0;
	int ret=sigaction(SIGINT,&act,&oldaction);
	if(ret == -1){
		sys_err("sigaction error");
	}
	while(1);

return 0;
}
