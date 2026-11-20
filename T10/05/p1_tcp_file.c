#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 5052

int main(){
    int s=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv,cli;
    socklen_t cl;

    serv.sin_family=AF_INET;
    serv.sin_addr.s_addr=htonl(INADDR_ANY);
    serv.sin_port=htons(PORT);

    bind(s,(struct sockaddr*)&serv,sizeof(serv));
    listen(s,5);
    printf("FILE SERVER on %d\n",PORT);

    while(1){
        int c=accept(s,(struct sockaddr*)&cli,&cl);
        char fname[256]; int n;
        n=recv(c,fname,255,0); fname[n]=0;
        FILE*f=fopen(fname,"r");
        if(!f){ send(c,"ERROR\n",6,0); close(c); continue; }
        char buf[512];
        while(fgets(buf,512,f))send(c,buf,strlen(buf),0);
        fclose(f); close(c);
    }
}