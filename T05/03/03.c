#include <stdio.h>

extern char **environ;

int main(int argc, char *argv[]) {
    printf("Argumenty programu:\n");
    for (int i = 0; i < argc; i++)
        printf("argv[%d] = %s\n", i, argv[i]);

    printf("\nProstredie:\n");
    for (char **env = environ; *env; env++)
        printf("%s\n", *env);
    return 0;
}
