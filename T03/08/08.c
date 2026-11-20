#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    char *path = argc > 1 ? argv[1] : ".";
    DIR *d = opendir(path);
    if(!d) return 1;

    struct dirent *entry;
    while((entry = readdir(d)) != NULL) {
        struct stat st;
        stat(entry->d_name, &st);
        printf("%10lld %s\n", (long long)st.st_size, entry->d_name);
    }
    closedir(d);
    return 0;
}
