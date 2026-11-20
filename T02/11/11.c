#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("testfile11.txt", O_CREAT | O_RDWR, 0644);
    write(fd, "abcdefghijklmnopqrstuvwxyz1234", 30);

    lseek(fd, 10, SEEK_SET);
    write(fd, "AAA", 3);

    lseek(fd, 0, SEEK_SET);
    char buf[31];
    read(fd, buf, 30);
    buf[30] = '\0';
    printf("%s\n", buf);

    close(fd);
    return 0;
}
