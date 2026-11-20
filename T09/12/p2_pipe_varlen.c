#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME "varpipe"

int main(){
    mkfifo(FIFO_NAME,0666);
    int fd=open(FIFO_NAME,O_RDONLY);
    while(1){
        int len;
        if(read(fd,&len,sizeof(int))<=0) break;
        char* buf=malloc(len+1);
        if(read(fd,buf,len)<=0){free(buf);break;}
        buf[len]='\0';
        printf("P2: %s",buf);
        free(buf);
    }
}