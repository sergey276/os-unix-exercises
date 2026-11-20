#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main() {
    char login[100], password[100];
    struct termios oldt, newt;

    printf("Login: ");
    scanf("%s", login);

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    printf("Heslo: ");
    scanf("%s", password);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    printf("\nZadane heslo: %s\n", password);

    return 0;
}
