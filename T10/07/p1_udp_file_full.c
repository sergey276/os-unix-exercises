#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 5054
#define CH 512

typedef struct {int last; int len; char data[CH];} PKT;

int main(){
    int s=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in serv,cli; socklen_t cl=sizeof(cli);
    serv.sin_family=AF_INET; serv.sin_addr.s_addr=htonl(INADDR_ANY);
    serv.sin_port=htons(PORT);
    bind(s,(struct sockaddr*)&serv,sizeof(serv));

    char fname[256];
    while(1){
        int n=recvfrom(s,fname,255,0,(struct sockaddr*)&cli,&cl);
        fname[n]=0;
        FILE*f=fopen(fname,"r");
        PKT p;
        if(!f){
            p.last=1; p.len=sprintf(p.data,"ERR\n");
            sendto(s,&p,sizeof(p),0,(struct sockaddr*)&cli,cl);
            continue;
        }
        while((p.len=fread(p.data,1,CH,f))>0){
            p.last=0;
            sendto(s,&p,sizeof(p),0,(struct sockaddr*)&cli,cl);
        }
        p.last=1; p.len=0;
        sendto(s,&p,sizeof(p),0,(struct sockaddr*)&cli,cl);
        fclose(f);
    }
}