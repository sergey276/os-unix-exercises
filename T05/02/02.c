#include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("Pred exec: PID=%d, PPID=%d\n", getpid(), getppid());
    execl("/bin/ls", "ls", "-l", NULL);
    perror("execl zlyhal");
    return 1;
}
