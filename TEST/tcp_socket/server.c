#define SERV_PORT 9527
#include"wrap.h"
int main(int argc,char *argv[]){
    int lfd=0, cfd=0;
    int ret,i;
    char buf[BUFSIZ],client_IP[1024];
    struct sockaddr_in serv_addr,client_addr;
    socklen_t client_addr_len;
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    lfd=Socket(AF_INET,SOCK_STREAM,0);
    printf("创建socket成功！\n");
    bind(lfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    printf("建立连接！\n");
    listen(lfd,128);
    printf("监听成功！\n");
    printf("1\n");
    client_addr_len=sizeof(client_addr);
    printf("2\n");
    printf("client_addr的大小: %lu",sizeof(client_addr));
    cfd = accept(lfd,(struct sockaddr*)&client_addr,&client_addr_len);
    //client_addr_len=sizeof(client_addr);
    printf("client_addr的大小: %lu",sizeof(client_addr));
    if(cfd==-1){
        sys_err("accept error");
    }
    printf("client ip:%s port:%d\n",
    inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,client_IP,sizeof(client_IP)),
    ntohs(client_addr.sin_port));
    while(1){
        ret = read(cfd,buf,sizeof(buf));
        write(STDOUT_FILENO,buf,ret);
        for(i=0;i<ret;i++){
            buf[i]=toupper(buf[i]);
        }
        write(cfd,buf,ret);
    }
    close(lfd);
    close(cfd);

    return 0;
}
