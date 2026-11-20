#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    char cmd[128];
    while (1) {
        printf("shell> ");
        if (!fgets(cmd, sizeof(cmd), stdin)) break;
        cmd[strcspn(cmd, "\n")] = 0;
        if (strcmp(cmd, "exit") == 0) break;
        execl(cmd, cmd, NULL);
        perror("exec zlyhal");
    }
    return 0;
}
