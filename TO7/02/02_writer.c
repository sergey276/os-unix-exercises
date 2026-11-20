#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
extern char **environ;
int main(void){
    int fd[2]; if(pipe(fd)==-1){perror("pipe");exit(EXIT_FAILURE);}
    const char *msg="Data pre druhy program cez pipe.\n";
    write(fd[1],msg,strlen(msg)); close(fd[1]);
    char fdstr[16]; snprintf(fdstr,sizeof(fdstr),"%d",fd[0]);
    char *argv[]={"./02_reader",fdstr,NULL};
    execve("./02_reader",argv,environ);
    perror("execve"); return 1;
}
