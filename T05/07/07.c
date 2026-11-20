#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main(void) {
    pid_t pid = fork();
    if (pid == 0)
        printf("Potomok: PATH=%s\n", getenv("PATH"));
    else
        printf("Rodič: PATH=%s\n", getenv("PATH"));
    return 0;
}
