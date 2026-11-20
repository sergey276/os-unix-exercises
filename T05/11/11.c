#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    pid_t pid = fork();

    for (int i = 0; i < 5; i++) {
        dprintf(fd, "PID=%d: riadok %d\n", getpid(), i);
        usleep(100000);
    }

    close(fd);
    return 0;
}
