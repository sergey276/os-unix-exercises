#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_KEY 0x1111
#define SHM_SIZE 2048

typedef struct{ int valid; char buffer[1024]; } shmseg;

int main(){
    int shmid=shmget(SHM_KEY,SHM_SIZE,0);
    if(shmid==-1){ perror("shmget"); return 1;}
    shmseg* shm=shmat(shmid,NULL,0);
    if(shm==(void*)-1){ perror("shmat"); return 1;}

    while(1){
        if(shm->valid==1){
            if(__sync_bool_compare_and_swap(&shm->valid,1,2)){
                printf("%s",shm->buffer);
                shm->valid=0;
            }
        }
        usleep(5000);
    }
}