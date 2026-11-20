#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

int main() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    int c = 0, k = 1, rv;
    while(1) {
        printf(" %d \r", c);
        fflush(stdout);
        usleep(500000);
        c = c + k;
        rv = getchar();
        if(rv >= '0' && rv <= '9') k = rv - '0';
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;
}
