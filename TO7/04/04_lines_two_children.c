#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
int main(int argc,char*argv[]){
 if(argc!=3){fprintf(stderr,"Pouzitie: %s <tty1> <tty2>\n",argv[0]);return 1;}
 int p[2]; pipe(p);
 if(fork()==0){close(p[1]);int t=open(argv[1],O_WRONLY);char c,line[256];int pos=0;
 while(read(p[0],&c,1)>0){line[pos++]=c;if(c=='\n'){write(t,line,pos);pos=0;}}
 return 0;}
 if(fork()==0){close(p[1]);int t=open(argv[2],O_WRONLY);char c,line[256];int pos=0;
 while(read(p[0],&c,1)>0){line[pos++]=c;if(c=='\n'){write(t,line,pos);pos=0;}}
 return 0;}
 close(p[0]);
 const char*msg[]={"Prvy riadok\n","Druhy, dlhsi riadok\n","Treti\n"};
 for(int i=0;i<9;i++){write(p[1],msg[i%3],strlen(msg[i%3]));usleep(300000);}
 close(p[1]);wait(NULL);wait(NULL);
}
