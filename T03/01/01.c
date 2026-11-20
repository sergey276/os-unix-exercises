#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd1 = open("testfile.txt", O_CREAT | O_RDWR, 0644);
    if(fd1 < 0) return 1;

    int fd2 = dup(fd1); // duplikát
    write(fd1, "Hello", 5);
    lseek(fd1, 0, SEEK_SET);

    char buf[10];
    read(fd2, buf, 5); // čítanie z dup
    buf[5] = '\0';
    printf("Prečítané zo zduplikovaného FD: %s\n", buf);

    close(fd1);
    close(fd2);
    return 0;
}
