#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define SHM_KEY 0x3333
#define SHM_SIZE 2048
#define FIFO_NAME "syncfifo"

typedef struct { char buffer[1024]; } shmseg;

int main(){
    int shmid=shmget(SHM_KEY,SHM_SIZE,IPC_CREAT|0666);
    shmseg* shm=shmat(shmid,NULL,0);
    mkfifo(FIFO_NAME,0666);
    int fd=open(FIFO_NAME,O_WRONLY);
    char line[1024];
    while(1){
        printf(">> "); fflush(stdout);
        if(!fgets(line,1024,stdin)) break;
        strcpy(shm->buffer,line);
        char x='X'; write(fd,&x,1);
    }
}