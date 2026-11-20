#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void){
    int fd[2];
    if(pipe(fd)==-1){perror("pipe");exit(EXIT_FAILURE);}
    const char *msg="Ahoj z pipe-u!\n";
    size_t len=strlen(msg);
    write(fd[1],msg,len);
    close(fd[1]);
    char buf[128];
    ssize_t n=read(fd[0],buf,sizeof(buf)-1);
    buf[n]='\0';
    printf("Precital som: %s",buf);
    close(fd[0]);
}
