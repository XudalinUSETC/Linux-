#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int create_listenfd(void)
{
 
    int fd=socket(AF_INET,SOCK_STREAM,0);
    int n=1;
    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&n,4);
    struct sockaddr_in sin;
    bzero(&sin,sizeof(sin));
    sin.sin_family=AF_INET;
    sin.sin_port=htons(80);
    sin.sin_addr.s_addr=INADDR_ANY;

    int res=bind(fd,(struct sockaddr *)&sin,sizeof(sin));
    if(res==-1)
    {
        perror("bind");
        exit(1);
    }

    listen(fd,100);
    return fd;    
}

//处理客户端的请求
void handle_request(int fd)
{
    //客户端首先会发一个字符串(请求)过来
    char buffer[1024*1024]={0};
    int nread=read(fd,buffer,sizeof(buffer));
    printf("读到的请求是%s\n",buffer);

    //从请求里解析出文件名来
    char filename[10]={0};
    sscanf(buffer,"GET /%s",filename);//字符串解析
    printf("解析的文件名是%s\n",filename);

    //根据文件名获得mime文件类型,用放入响应头中,告诉浏览器我发给你的是什么类型的文件
    char *mime=NULL;
    if(strstr(filename,".html"))
    mime="text/html";
    else if(strstr(filename,".jpg"))
    mime="image/jpg";

    //打开文件,读取内容,构建响应,发回给客户端
    char response[1024*1024]={0};
    sprintf(response,"HTTP/1.1 200 OK\r\nContent-Type: %s\r\n\r\n",mime);
    int headlen=strlen(response);

    int filefd=open(filename,O_RDONLY);
    int filelen=read(filefd,response+headlen,sizeof(response)-headlen);

    //发送响应头+内容
    write(fd,response,headlen+filelen);
    close(filefd);
    sleep(1);
}


int main(void)
{
    //1 创建监听套接字,返回是套接字描述符
    int sockfd=create_listenfd();
    

    while(1)
    {
        //2 接受客户端连接
        int fd=accept(sockfd,NULL,NULL);
        printf("有客户端连接\n");    
        //3、处理客户端发来的请求
        handle_request(fd);   
        close(fd);
    }

    close(sockfd);
}







