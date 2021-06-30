#define SERV_PORT 9999
#include"wrap.h"
int main(int argc,char *argv[]){
    int cfd;
    int conter=10;
    char buf[BUFSIZ];

    struct sockaddr_in serv_addr;   //服务器地址结构
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(SERV_PORT);
    inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr.s_addr);

    socket(AF_INET,SOCK_STREAM,0);
    connect(cfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    while(--conter){
        write(cfd,"hello\n",6);
       int ret = read(cfd,buf,sizeof(buf));
        write(STDOUT_FILENO,buf,ret);
        sleep(1);
    }
    close(cfd);
    return 0;
}
