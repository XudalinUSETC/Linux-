#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/mman.h>
#include<arpa/inet.h>
int main(int argc,char* argv[]){

	char *p=NULL;
	int fd;
	fd = open("testmap2",O_RDWR|O_CREAT|O_TRUNC,0644);
	if(fd== -1){
		perror("open error");
		exit(1);
	}
	lseek(fd,10,SEEK_END);
	write(fd,"\0",1);
	int len = lseek(fd,0,SEEK_END);
//	int len=20;
	p = mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);
	if(p==MAP_FAILED){
		perror("mmap error");
		exit(1);
	}
	strcpy(p,"hello mmap");
	printf("------%s\n",p);
	int ret = munmap(p,len);
	if(ret == -1){
		perror("munmap error");
		exit(1);
	}
	return 0;
}
