#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd1 = open("testfile.txt", O_CREAT | O_RDWR, 0644);
    int fd2 = dup(fd1);

    write(fd1, "ABC", 3);
    lseek(fd1, 0, SEEK_SET);

    char c;
    read(fd2, &c, 1);
    printf("Čítanie cez dup(): %c\n", c);

    close(fd1);
    close(fd2);
    return 0;
}
