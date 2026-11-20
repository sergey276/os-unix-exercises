// p1_sem.c - producer
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <errno.h>

#define SHM_KEY  0x4444
#define SEM_KEY  0x5555
#define BUFFER_SLOTS 1
#define SEM_MUTEX  0
#define SEM_ITEMS  1
#define SEM_SPACES 2

typedef struct { int in,out,count; char buffer[BUFFER_SLOTS][1024]; } shmseg;
union semun{int val; struct semid_ds* buf; unsigned short* array;};

int sem_op(int id,int num,int op){ struct sembuf sb={num,op,0}; return semop(id,&sb,1); }

int main(){
    int shmid=shmget(SHM_KEY,sizeof(shmseg),IPC_CREAT|IPC_EXCL|0666);
    int first=0;
    if(shmid==-1){
        if(errno==EEXIST) shmid=shmget(SHM_KEY,sizeof(shmseg),0);
        else{perror("shmget");return 1;}
    } else first=1;

    shmseg* shm=shmat(shmid,NULL,0);
    if(shm==(void*)-1){ perror("shmat"); return 1; }
    if(first) shm->in=shm->out=shm->count=0;

    int semid=semget(SEM_KEY,3,IPC_CREAT|IPC_EXCL|0666);
    if(semid==-1){
        if(errno==EEXIST) semid=semget(SEM_KEY,3,0);
        else{perror("semget");return 1;}
    } else {
        union semun u;
        u.val=1; semctl(semid,SEM_MUTEX,SETVAL,u);
        u.val=0; semctl(semid,SEM_ITEMS,SETVAL,u);
        u.val=BUFFER_SLOTS; semctl(semid,SEM_SPACES,SETVAL,u);
    }

    char line[1024];
    while(1){
        printf(">> "); fflush(stdout);
        if(!fgets(line,1024,stdin)) break;
        sem_op(semid,SEM_SPACES,-1);
        sem_op(semid,SEM_MUTEX,-1);
        strncpy(shm->buffer[shm->in],line,1023);
        shm->buffer[shm->in][1023]='\0';
        shm->in=(shm->in+1)%BUFFER_SLOTS;
        sem_op(semid,SEM_MUTEX,1);
        sem_op(semid,SEM_ITEMS,1);
    }
    return 0;
}