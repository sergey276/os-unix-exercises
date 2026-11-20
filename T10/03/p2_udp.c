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
    struct sockaddr_in serv,from;
    socklen_t fl=sizeof(from);
    serv.sin_family=AF_INET;
    serv.sin_port=htons(PORT);
    inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr);

    char line[1024],buf[1024]; int n;
    while(1){
        printf(">> "); fflush(stdout);
        if(!fgets(line,1024,stdin))break;
        sendto(sockfd,line,strlen(line),0,(struct sockaddr*)&serv,sizeof(serv));
        n=recvfrom(sockfd,buf,1023,0,(struct sockaddr*)&from,&fl);
        buf[n]=0;
        printf("CLIENT: %s",buf);
    }
}