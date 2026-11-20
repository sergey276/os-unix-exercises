#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if(argc != 2) return 1;

    struct stat st;
    if(stat(argv[1], &st) == -1) return 1;

    printf("i-uzol súboru %s: %llu\n", argv[1], (unsigned long long)st.st_ino);
    return 0;
}
