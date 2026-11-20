#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define SHM_KEY 0x2222
#define SHM_SIZE 2048
#define READYFILE "ready.dat"
#define LOCKFILE "lock.dat"

typedef struct{ char buffer[1024]; } shmseg;

int main(){
    int shmid=shmget(SHM_KEY,SHM_SIZE,0);
    if(shmid==-1){ perror("shmget"); return 1;}
    shmseg* shm=shmat(shmid,NULL,0);
    if(shm==(void*)-1){ perror("shmat"); return 1;}

    while(1){
        int r=open(READYFILE,O_RDONLY);
        if(r==-1){ usleep(10000); continue; }
        close(r);

        int l=open(LOCKFILE,O_CREAT|O_EXCL|O_WRONLY,0666);
        if(l==-1){ usleep(5000); continue; }
        close(l);

        unlink(READYFILE);
        unlink(LOCKFILE);
        printf("%s",shm->buffer);
    }
}