#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 5050

int main(){
    int sockfd;
    struct sockaddr_in serv;
    sockfd=socket(AF_INET,SOCK_STREAM,0);

    serv.sin_family=AF_INET;
    serv.sin_port=htons(PORT);
    inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr);

    connect(sockfd,(struct sockaddr*)&serv,sizeof(serv));

    char line[1024],recvb[1024]; int n;
    while(1){
        printf(">> "); fflush(stdout);
        if(!fgets(line,1024,stdin))break;
        send(sockfd,line,strlen(line),0);
        n=recv(sockfd,recvb,1023,0);
        if(n<=0)break;
        recvb[n]=0;
        printf("CLIENT: %s",recvb);
    }
    close(sockfd);
}