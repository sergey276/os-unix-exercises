#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define SHM_KEY 0x3333
#define SHM_SIZE 2048
#define FIFO_NAME "syncfifo"

typedef struct{ char buffer[1024]; } shmseg;

int main(){
    int shmid=shmget(SHM_KEY,SHM_SIZE,0);
    if(shmid==-1){ perror("shmget"); return 1;}
    shmseg* shm=shmat(shmid,NULL,0);
    if(shm==(void*)-1){ perror("shmat"); return 1;}

    mkfifo(FIFO_NAME,0666);
    int fd=open(FIFO_NAME,O_RDONLY);
    if(fd==-1){ perror("fifo"); return 1;}

    char t;
    while(read(fd,&t,1)>0){
        printf("%s",shm->buffer);
    }
    return 0;
}