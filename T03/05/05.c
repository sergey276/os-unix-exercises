#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("fileA.txt", O_CREAT | O_RDWR, 0644);
    link("fileA.txt", "fileB.txt"); // hard link

    write(fd, "X", 1); // zapíš do fileA.txt
    close(fd);

    int fd2 = open("fileB.txt", O_RDONLY);
    char c;
    read(fd2, &c, 1);
    printf("Zápis cez fileA.txt ovplyvnil fileB.txt: %c\n", c);
    close(fd2);

    return 0;
}
