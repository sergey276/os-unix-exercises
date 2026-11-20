#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    char c;
    while(1) {
        int rv = read(STDIN_FILENO, &c, 1);
        if(rv > 0) printf("Naposledy zadany znak: %c\n", c);
        usleep(500000);
    }
    return 0;
}
