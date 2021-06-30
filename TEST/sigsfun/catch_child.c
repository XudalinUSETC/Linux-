#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<signal.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<arpa/inet.h>
void sys_err(const char* str){
	perror(str);
	exit(1);
}
void catch_child(int signo){
	pid_t wpid;
	int status;
	while((wpid=waitpid(-1,&status,0))!= -1){    //fangzhi duoge jincheng tongshi siwang xingcheng jiangshi jincheng
		if(WIFEXITED(status))
			printf("--------catch child id %d,ret=%d\n",wpid,WEXITSTATUS(status));
	}
	return ;
}
int main(int argc,char* argv[]){
	pid_t pid;

	int i;
	for(i=0;i<15;i++){
		if((pid=fork())==0)
			break;
	}
	if(i==15){
		struct sigaction act;
		sigset_t set;
		sigemptyset(&set);
		sigaddset(&set,SIGCHLD);
		sigprocmask(SIG_BLOCK,&set,NULL);

		act.sa_handler = catch_child;
		sigemptyset(&act.sa_mask);
		act.sa_flags=0;

		sigaction(SIGCHLD ,& act,NULL);
		sigprocmask(SIG_UNBLOCK,&set,NULL);

		printf("I'm parent,pid= %d\n",getpid());
		while(1);

	}
	else{
		printf("I'm child,pid= %d\n",getpid());
		return i+1;

	}

return 0;
}
