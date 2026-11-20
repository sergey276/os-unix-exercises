#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>

#define SHM_KEY 0x2222
#define SHM_SIZE 2048
#define FLAGFILE "flagfile.dat"

typedef struct{ char buffer[1024]; } shmseg;

int main(){
    int shmid=shmget(SHM_KEY,SHM_SIZE,IPC_CREAT|0666);
    if(shmid==-1){ perror("shmget"); return 1;}
    shmseg* shm=shmat(shmid,NULL,0);
    if(shm==(void*)-1){ perror("shmat"); return 1;}

    char line[1024];
    while(1){
        printf(">> "); fflush(stdout);
        if(!fgets(line,1024,stdin)) break;
        strcpy(shm->buffer,line);
        int fd=open(FLAGFILE,O_CREAT|O_WRONLY|O_TRUNC,0666);
        if(fd!=-1) close(fd);
    }
    shmdt(shm);
    return 0;
}