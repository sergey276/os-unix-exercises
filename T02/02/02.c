#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main() {
    int fd = open("testfile2.txt", O_CREAT | O_EXCL | O_RDWR, 0644);
    if(fd == -1) perror("O_CREAT|O_EXCL (nový súbor)");
    else {
        printf("Vytvorený nový súbor fd=%d\n", fd);
        close(fd);
    }

    fd = open("testfile2.txt", O_CREAT | O_EXCL | O_RDWR, 0644);
    if(fd == -1) perror("O_CREAT|O_EXCL (existujúci súbor)");
    else {
        printf("Otvorený existujúci súbor fd=%d\n", fd);
        close(fd);
    }
    return 0;
}
