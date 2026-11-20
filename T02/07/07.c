#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 4096

int main() {
    char buf[BUF_SIZE];
    ssize_t n;
    while((n = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
        write(STDOUT_FILENO, buf, n);
    }
    return 0;
}
