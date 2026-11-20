#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
    for (int i = 0; i < 3; i++) {
        char fname[32];
        sprintf(fname, "vystup%d.txt", i);
        int fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        int saved = dup(1);
        dup2(fd, 1);
        printf("Spustenie č.%d – PID=%d\n", i, getpid());
        fflush(stdout);
        dup2(saved, 1);
        close(fd);
    }
    return 0;
}
