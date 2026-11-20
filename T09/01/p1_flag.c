#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_KEY 0x1111
#define SHM_SIZE 2048

typedef struct {
    int valid;
    char buffer[1024];
} shmseg;

int main(void)
{
    int shmid;
    shmseg *shm;

    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) { perror("shmget"); return 1; }

    shm = shmat(shmid, NULL, 0);
    if (shm == (void*)-1){ perror("shmat"); return 1; }

    shm->valid = 0;

    char line[1024];
    while(1){
        printf(">> "); fflush(stdout);
        if(!fgets(line,1024,stdin)) break;
        while(shm->valid==1) usleep(10000);
        strcpy(shm->buffer,line);
        shm->valid=1;
    }
    shmdt(shm);
    return 0;
}