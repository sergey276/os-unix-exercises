#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if(argc != 3) {
        printf("Použitie: %s cieľ zdroj\n", argv[0]);
        return 1;
    }
    if(link(argv[2], argv[1]) == -1) {
        perror("link");
        return 1;
    }
    printf("Hard link vytvorený: %s -> %s\n", argv[1], argv[2]);
    return 0;
}
