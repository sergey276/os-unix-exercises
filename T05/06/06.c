#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t pid = fork();
    if (pid == 0) {
        printf("Potomok: argv[0]=%s\n", argv[0]);
    } else {
        printf("Rodič: argv[0]=%s\n", argv[0]);
    }
    return 0;
}
