#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <stdint.h>
#include <time.h>

static ssize_t read_all(int fd,void*b,size_t n){
 size_t r=0; while(r<n){ssize_t x=read(fd,(char*)b+r,n-r); if(x<=0)return x; r+=x;} return r;
}
int main(int argc,char*argv[]){
 if(argc<2){fprintf(stderr,"Pouzitie: %s <tty1> [tty2]…\n",argv[0]);return 1;}
 int p[2]; pipe(p); srand(time(NULL)); int n=argc-1;
 for(int i=0;i<n;i++)if(fork()==0){
  close(p[1]);int t=open(argv[i+1],O_WRONLY);
  while(1){uint32_t l; if(read_all(p[0],&l,4)<=0)break;
   char*s=malloc(l+1);read_all(p[0],s,l);s[l]=0;dprintf(t,"Child %d: %s\n",i,s);free(s);}
  return 0;}
 close(p[0]);
 for(int i=0;i<8;i++){uint32_t l=(rand()%20)+5;char*s=malloc(l);
  for(uint32_t j=0;j<l;j++)s[j]='a'+rand()%26;
  printf("Send %u: %.*s\n",l,l,s);
  write(p[1],&l,4);write(p[1],s,l);free(s);sleep((rand()%3)+1);}
 close(p[1]);for(int i=0;i<n;i++)wait(NULL);
}
