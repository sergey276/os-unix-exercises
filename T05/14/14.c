#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    char line[256];
    while (1) {
        printf("shell> ");
        if (!fgets(line, sizeof(line), stdin)) break;
        line[strcspn(line, "\n")] = 0;
        if (strncmp(line, "cd ", 3) == 0) {
            chdir(line + 3);
            continue;
        }
        if (strcmp(line, "exit") == 0) break;
        pid_t pid = fork();
        if (pid == 0) {
            execlp("/bin/sh", "sh", "-c", line, NULL);
            perror("exec");
            return 1;
        } else {
            wait(NULL);
        }
    }
    return 0;
}
