#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define SHM_KEY 0x2222
#define SHM_SIZE 2048
#define FLAGFILE "flagfile.dat"

typedef struct{ char buffer[1024]; } shmseg;

int main(){
    int shmid=shmget(SHM_KEY,SHM_SIZE,0);
    if(shmid==-1){ perror("shmget"); return 1;}
    shmseg* shm=shmat(shmid,NULL,0);
    if(shm==(void*)-1){ perror("shmat"); return 1;}

    while(1){
        int fd=open(FLAGFILE,O_RDONLY);
        if(fd==-1){
            usleep(10000);
            continue;
        }
        close(fd);
        unlink(FLAGFILE);
        printf("%s",shm->buffer);
    }
}