#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main() {
    int fd = open("testfile1.txt", O_RDWR, 0644); // без O_CREAT
    if(fd == -1) perror("open без O_CREAT");
    else {
        printf("Файл открыт без O_CREAT, fd=%d\n", fd);
        close(fd);
    }

    fd = open("testfile1.txt", O_CREAT | O_RDWR, 0644); // с O_CREAT
    if(fd == -1) perror("open с O_CREAT");
    else {
        printf("Файл открыт с O_CREAT, fd=%d\n", fd);
        close(fd);
    }
    return 0;
}
