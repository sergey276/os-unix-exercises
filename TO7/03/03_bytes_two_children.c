#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
int main(int argc,char*argv[]){
 if(argc!=3){fprintf(stderr,"Pouzitie: %s <tty1> <tty2>\n",argv[0]);return 1;}
 int p[2]; pipe(p);
 if(fork()==0){close(p[1]);int t=open(argv[1],O_WRONLY);
 char c;while(read(p[0],&c,1)>0) write(t,&c,1);return 0;}
 if(fork()==0){close(p[1]);int t=open(argv[2],O_WRONLY);
 char c;while(read(p[0],&c,1)>0) write(t,&c,1);return 0;}
 close(p[0]);
 const char*msg="abcdefghijklm\n";
 for(int i=0;i<20;i++){write(p[1],msg,strlen(msg));usleep(200000);}
 close(p[1]); wait(NULL); wait(NULL);
}
