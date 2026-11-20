#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main() {
    struct stat st;
    if(stat("testfile.txt", &st) == -1) return 1;

    printf("Práva: %o\n", st.st_mode & 0777);
    printf("Veľkosť: %lld\n", (long long)st.st_size);
    printf("Vlastník: %d\n", st.st_uid);
    printf("Skupina: %d\n", st.st_gid);
    printf("Čas modifikácie: %s", ctime(&st.st_mtime));

    return 0;
}
