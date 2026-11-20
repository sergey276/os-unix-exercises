#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

#define SHM_KEY  0x5678
#define SHM_SIZE 1024

int main(void)
{
    int shmid;
    char *shmaddr;

    // ziskame existujuci segment
    shmid = shmget(SHM_KEY, SHM_SIZE, 0);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    // pripojime sa
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *) -1) {
        perror("shmat");
        return 1;
    }

    printf("P2: precitany retazec zo shared memory:\n");
    printf("%s", shmaddr);

    // odpojenie
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        return 1;
    }

    return 0;
}
