#ifndef __wrap_H__
#define __wrap_H__
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<pthread.h>
#include<ctype.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void sys_err(const char *str);
int Socket(int domain,int type,int protocol);
int Bind(int sockfd,struct sockaddr *my_addr,socklen_t addrlen);
int Listen(int s,int backlog);
int connect(int sockfd,const struct sockaddr *addr,socklen_t addrlen);




#endif
