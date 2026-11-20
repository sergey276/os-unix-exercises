#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int fd = open("testfile4.txt", O_CREAT | O_RDWR, 0644);
    write(fd, "1234567", 7);
    lseek(fd, 0, SEEK_SET);

    char buf[10];
    ssize_t n = read(fd, buf, 10);
    if(n == -1) perror("read");
    else printf("Prečítaných bajtov: %zd\n", n);

    close(fd);
    return 0;
}
