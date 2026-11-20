#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 5052

int main(){
    int s=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv;

    serv.sin_family=AF_INET;
    serv.sin_port=htons(PORT);
    inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr);

    connect(s,(struct sockaddr*)&serv,sizeof(serv));

    char fname[256]; printf("Subor: ");
    fgets(fname,256,stdin); fname[strcspn(fname,"\n")]=0;
    send(s,fname,strlen(fname),0);

    char buf[512]; int n;
    while((n=recv(s,buf,511,0))>0){ buf[n]=0; printf("%s",buf); }
    close(s);
}