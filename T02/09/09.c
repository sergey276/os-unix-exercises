#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int fd = open("testfile9.txt", O_CREAT | O_RDWR, 0644);
    write(fd, "1234567890", 10);

    off_t pos;
    pos = lseek(fd, 3, SEEK_SET);
    printf("SEEK_SET 3: %lld\n", (long long)pos);

    pos = lseek(fd, 2, SEEK_CUR);
    printf("SEEK_CUR 2: %lld\n", (long long)pos);

    pos = lseek(fd, -4, SEEK_END);
    printf("SEEK_END -4: %lld\n", (long long)pos);

    close(fd);
    return 0;
}
