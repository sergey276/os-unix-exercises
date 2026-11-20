#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SHM_KEY  0x5678
#define SHM_SIZE 1024

int main(void)
{
    int shmid;
    char *shmaddr;
    char buffer[SHM_SIZE];

    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *) -1) {
        perror("shmat");
        return 1;
    }

    printf("P1_loop: zadavaj retazce (Ctrl+D/Ctrl+C na ukoncenie):\n");

    while (1) {
        printf(">> ");
        fflush(stdout);

        if (!fgets(buffer, sizeof(buffer), stdin)) {
            // EOF alebo chyba
            break;
        }

        strncpy(shmaddr, buffer, SHM_SIZE - 1);
        shmaddr[SHM_SIZE - 1] = '\0';

        // malá pauza, aby sme videli zmeny
        // (nie je nutna, len pre prehladnost)
        usleep(100000);
    }

    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
    }

    return 0;
}
