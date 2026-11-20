#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 5050
#define BACKLOG 5

int main(void){
    int listen_fd, conn_fd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_len;
    char buf[1024];
    int n;

    srand(time(NULL));

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt=1; setsockopt(listen_fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(PORT);

    bind(listen_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    listen(listen_fd,BACKLOG);
    printf("SERVER: listening on %d...\n",PORT);

    while(1){
        cli_len=sizeof(cli_addr);
        conn_fd=accept(listen_fd,(struct sockaddr*)&cli_addr,&cli_len);

        while((n=recv(conn_fd,buf,sizeof(buf)-1,0))>0){
            buf[n]=0;
            printf("SERVER received: %s",buf);
            sleep((rand()%3)+1);
            send(conn_fd,"VYPISANE!\n",11,0);
        }
        close(conn_fd);
    }
}