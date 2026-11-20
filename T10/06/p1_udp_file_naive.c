#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 5053

int main(){
    int s=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in serv,cli; socklen_t cl=sizeof(cli);
    serv.sin_family=AF_INET; serv.sin_addr.s_addr=htonl(INADDR_ANY);
    serv.sin_port=htons(PORT);
    bind(s,(struct sockaddr*)&serv,sizeof(serv));

    char fname[256],big[4096]; int n;
    while(1){
        n=recvfrom(s,fname,255,0,(struct sockaddr*)&cli,&cl);
        fname[n]=0;
        FILE*f=fopen(fname,"r");
        if(!f){sendto(s,"ERR",3,0,(struct sockaddr*)&cli,cl);continue;}
        int r=fread(big,1,4095,f); big[r]=0;
        sendto(s,big,r,0,(struct sockaddr*)&cli,cl);
        fclose(f);
    }
}