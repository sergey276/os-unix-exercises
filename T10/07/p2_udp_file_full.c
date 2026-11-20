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
    struct sockaddr_in serv,from; socklen_t fl=sizeof(from);
    serv.sin_family=AF_INET; serv.sin_port=htons(PORT);
    inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr);

    char fname[256];
    printf("Subor: "); fgets(fname,256,stdin); fname[strcspn(fname,"\n")]=0;
    sendto(s,fname,strlen(fname),0,(struct sockaddr*)&serv,sizeof(serv));

    PKT p;
    while(1){
        int n=recvfrom(s,&p,sizeof(p),0,(struct sockaddr*)&from,&fl);
        if(p.len>0) fwrite(p.data,1,p.len,stdout);
        if(p.last) break;
    }
}