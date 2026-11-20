#include <stdio.h>
#include <unistd.h>

int main(void) {
    int x = 42;
    pid_t pid = fork();
    if (pid == 0)
        printf("Potomok: x=%d\n", x);
    else
        printf("Rodič: x=%d\n", x);
    return 0;
}
