#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main(int argc,char* argv[]){

	int fd=open(argv[1],O_RDWR);
	int newfd = dup(fd);
	printf("newfd=%d\n",newfd);
	write(newfd,"1234567",7);
return 0;
}
