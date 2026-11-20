#include <stdio.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();
    if (pid == 0) {
        chdir("/tmp");
        printf("Potomok: aktuálny adresár zmenený na /tmp\n");
    } else {
        sleep(1);
        char buf[256];
        getcwd(buf, sizeof(buf));
        printf("Rodič: aktuálny adresár je %s\n", buf);
    }
    return 0;
}
