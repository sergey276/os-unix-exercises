#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int fd = open("testfile10.txt", O_CREAT | O_RDWR, 0644);
    write(fd, "ABCDEFGH", 8);

    lseek(fd, 1000, SEEK_END);
    write(fd, "XYZ", 3);

    lseek(fd, 0, SEEK_SET);
    char buf[20];
    ssize_t n = read(fd, buf, 20);
    for(ssize_t i=0;i<n;i++)
        printf("%02X ", (unsigned char)buf[i]);
    printf("\n");

    close(fd);
    return 0;
}
