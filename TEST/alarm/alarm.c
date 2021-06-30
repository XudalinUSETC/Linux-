#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int main(){
    int i;
    alarm(1);
    for(i=0;;i++){
        printf("%d\n",i);
    }
    return 0;
}
