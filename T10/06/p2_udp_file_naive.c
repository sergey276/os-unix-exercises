#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 5053

int main(){
    int s=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in serv,from; socklen_t fl=sizeof(from);
    serv.sin_family=AF_INET; serv.sin_port=htons(PORT);
    inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr);

    char fname[256],buf[4096]; int n;
    printf("Subor: "); fgets(fname,256,stdin); fname[strcspn(fname,"\n")]=0;
    sendto(s,fname,strlen(fname),0,(struct sockaddr*)&serv,sizeof(serv));

    n=recvfrom(s,buf,4095,0,(struct sockaddr*)&from,&fl);
    buf[n]=0;
    printf("%s",buf);
}