#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<ctype.h>

#define MAXLINE 8192
#define SERV_PORT 8000

struct s_info{
    struct sockaddr_in cliaddr;
    int connfd;
};
void sys_err(const char *str){
    perror(str);
    exit(1);
}
void *do_work(void *arg)
{
    int n,i;
    struct s_info *ts=(struct s_info*)arg;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];

    while(1){
        n=read(ts->connfd,buf,MAXLINE);
        if(n==0){
            printf("the client %d closed...\n",ts->connfd);
            break;
        }
        printf("received from %s at port %d\n",
                inet_ntop(AF_INET,&(*ts).cliaddr.sin_addr,str,sizeof(str)),
                ntohs((*ts).cliaddr.sin_port));
        for(i=0;i<n;i++)
            buf[i] = toupper(buf[i]);
        write(STDOUT_FILENO,buf,n);
        write(ts->connfd,buf,n);
    }
    close(ts->connfd);
    return NULL;
}

int main(void)
{
    struct sockaddr_in servaddr,cliaddr;
    socklen_t cliaddr_len;
    int listenfd,connfd;
    int ret;
    pthread_t tid;
    struct s_info ts[256];
    int i=0;
    listenfd=socket(AF_INET,SOCK_STREAM,0);
    if(listenfd== -1){
        sys_err("socket error");
    }
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    ret = bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    if(ret==-1){
        sys_err("bind error");
    }
    ret = listen(listenfd,128);
    if(ret==-1){
        sys_err("bind error");
    }
    printf("Accepting client connect...\n");
    while(1){
        cliaddr_len=sizeof(cliaddr);
        connfd = accept(listenfd,(struct sockaddr*)&cliaddr,&cliaddr_len);
        if(connfd == -1){
            sys_err("accept error");
        }
        ts[i].cliaddr = cliaddr;
        ts[i].connfd = connfd;
        pthread_create(&tid,NULL,do_work,(void*)&ts[i]);
        pthread_detach(tid);
        i++;

    }
    return 0;
}


