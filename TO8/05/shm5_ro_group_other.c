#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

#define SHM_SIZE 1024
#define SHM_KEY  0x1235

int main(void)
{
    int shmid;

    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | IPC_EXCL | 0644);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    printf("Vytvoreny segment: shmid = %d, key = 0x%x, mode = 0644\n",
           shmid, SHM_KEY);

    printf("Overte pomocou ipcs -m, ze prava su -rw-r--r--.\n");
    return 0;
}
