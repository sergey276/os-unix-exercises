#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int fd1 = open("mode1.txt", O_CREAT | O_RDWR, 0644);
    int fd2 = open("mode2.txt", O_CREAT | O_RDWR, 0600);
    if(fd1 == -1) perror("mode1");
    if(fd2 == -1) perror("mode2");

    close(fd1);
    close(fd2);

    printf("ls -l mode1.txt mode2.txt\n");
    system("ls -l mode1.txt mode2.txt");
    return 0;
}
