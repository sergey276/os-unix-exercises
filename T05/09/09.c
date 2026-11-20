#include <stdio.h>
#include <unistd.h>

int main(void) {
    int x = 42;
    pid_t pid = fork();
    if (pid == 0) {
        x = 99;
        printf("Potomok: x=%d\n", x);
    } else {
        sleep(1);
        printf("Rodič: x=%d\n", x);
    }
    return 0;
}
