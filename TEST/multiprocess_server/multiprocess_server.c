#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<signal.h>
#include<pthread.h>
#include<strings.h>
#include<ctype.h>
#define SRV_PORT 9999
void sys_err(const char *str){
	perror(str);
	exit(1);
}
void perr_exit(const char *s){
	perror(s);
	exit(1);
}
void catch_child(int signo){

	while(waitpid(0,NULL,WNOHANG)>0);
	return ;

}
int main(int argc,char* argv[]){
	int lfd,cfd;
	pid_t pid;
	int ret,i;
	struct sockaddr_in srv_addr,clt_addr;
	char buf[BUFSIZ];
	socklen_t clt_addr_len;

	bzero(&srv_addr,sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port=htons(SRV_PORT);
	srv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	lfd=socket(AF_INET,SOCK_STREAM,0);
	if(lfd == -1){
		sys_err("scoket error");
	}
	ret = bind(lfd,(struct sockaddr*)&srv_addr,sizeof(srv_addr));
	if(ret == -1){
		sys_err("bind error");
	}
	ret = listen(lfd,128);
	if(ret == -1){
		sys_err("listen error");
	}
	clt_addr_len=sizeof(clt_addr);
	while(1){
		cfd = accept(lfd,(struct sockaddr *)&clt_addr,&clt_addr_len);
		if(cfd == -1){
			sys_err("accept error");
		}
		pid = fork();
		if(pid<0){
			perr_exit("fork error");
		}else if(pid==0){
			close(lfd);
			break;
		}else{
			struct sigaction act;
			act.sa_handler = catch_child;
			sigemptyset(&act.sa_mask);
			act.sa_flags = 0;
			ret = sigaction(SIGCHLD,&act,NULL);
			if(ret!=0){
				perr_exit("sigaction error");
			}
			close(cfd);
			continue;

		}
	}
		if(pid==0){
			for(;;){
			ret =read(cfd,buf,sizeof(buf));
			if(ret==0){
				close(cfd);
				exit(1);
			}
			for(i=0;i<ret;i++){
				buf[i]=toupper(buf[i]);
			}
			write(cfd,buf,ret);
			write(STDOUT_FILENO,buf,ret);
		}

	}
return 0;
}
