#include <stdio.h>
#include <unistd.h>

int main(void) {
    char *args[] = {"./progB", "Ahoj", "svet", NULL};
    execv(args[0], args);
    perror("execv zlyhal");
    return 1;
}
