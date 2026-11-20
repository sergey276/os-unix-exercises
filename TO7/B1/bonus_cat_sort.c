#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
extern char **environ;
int main(int argc,char*argv[]){
 if(argc!=2){fprintf(stderr,"Pouzitie: %s <subor>\n",argv[0]);return 1;}
 int p[2];pipe(p);
 if(fork()==0){dup2(p[1],STDOUT_FILENO);close(p[0]);close(p[1]);
  char*av[]={"cat",argv[1],NULL};execve("/bin/cat",av,environ);perror("cat");exit(1);}
 if(fork()==0){dup2(p[0],STDIN_FILENO);close(p[0]);close(p[1]);
  char*av[]={"sort",NULL};execve("/usr/bin/sort",av,environ);perror("sort");exit(1);}
 close(p[0]);close(p[1]);wait(NULL);wait(NULL);
}
