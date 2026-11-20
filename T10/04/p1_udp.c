#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 5051

int main(){
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in serv,cli;
    socklen_t cl=sizeof(cli);
    char buf[1024]; int n;

    serv.sin_family=AF_INET;
    serv.sin_addr.s_addr=htonl(INADDR_ANY);
    serv.sin_port=htons(PORT);

    bind(sockfd,(struct sockaddr*)&serv,sizeof(serv));
    printf("UDP SERVER listening %d\n",PORT);

    while(1){
        n=recvfrom(sockfd,buf,1023,0,(struct sockaddr*)&cli,&cl);
        buf[n]=0;
        printf("SERVER recv: %s",buf);
        sleep((rand()%3)+1);
        sendto(sockfd,"VYPISANE!\n",11,0,(struct sockaddr*)&cli,cl);
    }
}