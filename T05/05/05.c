#include <stdio.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();
    if (pid == 0)
        printf("Som potomok. PID=%d, PPID=%d\n", getpid(), getppid());
    else
        printf("Som rodič. PID=%d, PPID=%d, PID potomka=%d\n", getpid(), getppid(), pid);
    return 0;
}
