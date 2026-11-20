#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_NAME "varpipe"

int main(){
    mkfifo(FIFO_NAME,0666);
    int fd=open(FIFO_NAME,O_WRONLY);
    char line[1024];
    while(1){
        printf(">> "); fflush(stdout);
        if(!fgets(line,1024,stdin)) break;
        int len=strlen(line);
        write(fd,&len,sizeof(int));
        write(fd,line,len);
    }
}