#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if(argc != 2) return 1;

    struct stat st;
    if(stat(argv[1], &st) == -1) return 1;

    if(S_ISDIR(st.st_mode)) printf("%s je adresár\n", argv[1]);
    else if(S_ISREG(st.st_mode)) printf("%s je súbor\n", argv[1]);
    else printf("%s je iný typ súboru\n", argv[1]);

    return 0;
}
