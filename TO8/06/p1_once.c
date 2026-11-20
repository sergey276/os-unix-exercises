#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>

#define SHM_KEY  0x5678
#define SHM_SIZE 1024

int main(void)
{
    int shmid;
    char *shmaddr;
    char buffer[SHM_SIZE];

    // nacitanie textu zo stdin (jedna riadkova veta)
    printf("Zadaj retazec: ");
    fflush(stdout);
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        fprintf(stderr, "Chyba pri citani vstupu\n");
        return 1;
    }

    // vytvorenie segmentu
    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    // pripojenie
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *) -1) {
        perror("shmat");
        return 1;
    }

    // zapis do zdieľanej pamäte
    strncpy(shmaddr, buffer, SHM_SIZE - 1);
    shmaddr[SHM_SIZE - 1] = '\0';

    printf("P1: zapisany retazec do shared memory.\n");

    // odpojenie
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        return 1;
    }

    return 0;
}
