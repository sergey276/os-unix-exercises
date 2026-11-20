#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc,char*argv[]){
    if(argc!=2){fprintf(stderr,"Pouzitie: %s <read_fd>\n",argv[0]);return 1;}
    int fd=atoi(argv[1]); char buf[256]; ssize_t n;
    while((n=read(fd,buf,sizeof(buf)))>0) write(STDOUT_FILENO,buf,n);
    close(fd);
}
