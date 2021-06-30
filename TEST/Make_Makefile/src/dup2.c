#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main(int argc,char* argv[]){

	int fd1=open(argv[1],O_RDWR);
	int fd2=open(argv[2],O_RDWR);
	int fdret = dup2(fd1,fd2);
	printf("fdret = %d\n",fdret);
	int ret = write(fd2,"1234567",7);
	printf("ret=%d\n",ret);
return 0;
}
