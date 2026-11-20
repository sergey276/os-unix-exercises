#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc != 5) {
        printf("Použitie: %s filename pos count char\n", argv[0]);
        return 1;
    }
    char *filename = argv[1];
    int pos = atoi(argv[2]);
    int count = atoi(argv[3]);
    char c = argv[4][0];

    int fd = open(filename, O_RDWR);
    if(fd == -1) { perror("open"); return 1; }

    lseek(fd, pos, SEEK_SET);
    for(int i=0;i<count;i++)
        write(fd, &c, 1);

    lseek(fd, 0, SEEK_SET);
    char buf[1024];
    ssize_t n = read(fd, buf, 1024);
    write(STDOUT_FILENO, buf, n);

    close(fd);
    return 0;
}
