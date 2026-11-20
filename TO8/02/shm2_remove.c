#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

#define SHM_KEY 0x1234

int main(void)
{
    int shmid;

    // najdeme existujuci segment
    shmid = shmget(SHM_KEY, 0, 0);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    // zmazanie segmentu
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl(IPC_RMID)");
        return 1;
    }

    printf("Segment so shmid = %d bol zmazany (IPC_RMID).\n", shmid);
    return 0;
}
