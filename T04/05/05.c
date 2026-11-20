#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ICANON;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int c;
    while((c=getchar())!=EOF) {
        putchar(c);
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;
}
