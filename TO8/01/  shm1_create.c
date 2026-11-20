#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

#define SHM_SIZE 1024   // 1 kB
#define SHM_KEY  0x1234 // ľubovoľný, ale fixný

int main(void)
{
    int shmid;

    // vytvorenie segmentu: rw pre užívateľa, skupinu a ostatných
    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | IPC_EXCL | 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    printf("Vytvoreny segment: shmid = %d, key = 0x%x, size = %d\n",
           shmid, SHM_KEY, SHM_SIZE);

    printf("Spustite: ipcs -m na zobrazenie segmentu.\n");
    return 0;
}
