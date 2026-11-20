#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

#define SHM_SIZE 1024

int main(void)
{
    int shmid;

    // IPC_PRIVATE vytvori novy, nezdielany cez key, ale stale ma shmid
    shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0600);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    printf("Vytvoreny IPC_PRIVATE segment: shmid = %d, size = %d\n",
           shmid, SHM_SIZE);
    printf("Overte pomocou ipcs -m (key bude 0).\n");

    // segment sa zmaze automaticky az ked ho nikto nepouziva + IPC_RMID,
    // ale tu ho nechame ziveho pre ipcs.
    return 0;
}
