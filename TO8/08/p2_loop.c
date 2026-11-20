#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SHM_KEY  0x5678
#define SHM_SIZE 1024

int main(void)
{
    int shmid;
    char *shmaddr;
    char last[SHM_SIZE] = {0};

    shmid = shmget(SHM_KEY, SHM_SIZE, 0);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *) -1) {
        perror("shmat");
        return 1;
    }

    printf("P2_loop: citam retazce zo shared memory (Ctrl+C na ukoncenie)\n");

    while (1) {
        // ked sa obsah zmenil, vypiseme ho
        if (strncmp(last, shmaddr, SHM_SIZE) != 0) {
            strncpy(last, shmaddr, SHM_SIZE - 1);
            last[SHM_SIZE - 1] = '\0';
            printf("P2_loop: novy retazec: %s", last);
            fflush(stdout);
        }

        usleep(200000); // 0.2 s
    }

    // sem sa realne nedostaneme (Ctrl+C), ale pre uplnost:
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
    }

    return 0;
}
