#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdint.h>
#include <time.h>
volatile sig_atomic_t go=0;
void h(int s){go=1;}
ssize_t ra(int fd,void*b,size_t n){size_t r=0;while(r<n){ssize_t x=read(fd,(char*)b+r,n-r);if(x<=0)return x;r+=x;}return r;}
int main(int argc,char*argv[]){
 if(argc<2){fprintf(stderr,"Pouzitie: %s <tty1> [tty2]…\n",argv[0]);return 1;}
 int p[2];pipe(p);srand(time(NULL));int n=argc-1;pid_t c[n];
 for(int i=0;i<n;i++)if((c[i]=fork())==0){
  signal(SIGUSR2,h);close(p[1]);int t=open(argv[i+1],O_WRONLY);
  while(1){if(!go){pause();continue;}go=0;uint32_t l;
   if(ra(p[0],&l,4)<=0)break;char*s=malloc(l+1);ra(p[0],s,l);s[l]=0;
   dprintf(t,"Child:%s\n",s);free(s);}return 0;}
 close(p[0]);
 for(int i=0;i<10;i++){uint32_t l=(rand()%20)+5;char*s=malloc(l);
  for(uint32_t j=0;j<l;j++)s[j]='a'+rand()%26;
  write(p[1],&l,4);write(p[1],s,l);kill(c[i%n],SIGUSR2);
  printf("Send %d: %.*s\n",i,l,s);free(s);sleep((rand()%3)+1);}
 close(p[1]);for(int i=0;i<n;i++)wait(NULL);
}
