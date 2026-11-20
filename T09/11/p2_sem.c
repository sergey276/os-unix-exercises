#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

#define SHM_KEY  0x4444
#define SEM_KEY  0x5555
#define BUFFER_SLOTS 5
#define SEM_MUTEX  0
#define SEM_ITEMS  1
#define SEM_SPACES 2

typedef struct { int in,out,count; char buffer[BUFFER_SLOTS][1024]; } shmseg;

int sem_op(int id,int num,int op){ struct sembuf sb={num,op,0}; return semop(id,&sb,1); }

int main(){
    int shmid=shmget(SHM_KEY,sizeof(shmseg),0);
    shmseg* shm=shmat(shmid,NULL,0);

    int semid=semget(SEM_KEY,3,0);

    while(1){
        sem_op(semid,SEM_ITEMS,-1);
        sem_op(semid,SEM_MUTEX,-1);
        char msg[1024];
        strcpy(msg,shm->buffer[shm->out]);
        shm->out=(shm->out+1)%BUFFER_SLOTS;
        sem_op(semid,SEM_MUTEX,1);
        sem_op(semid,SEM_SPACES,1);
        printf("P2: %s",msg);
        fflush(stdout);
    }
}