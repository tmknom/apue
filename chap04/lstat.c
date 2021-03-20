#include "apue.h"

int main(int argc, char *argv[]) {
    struct stat buf;
    char *ptr;

    for (int i = 1; i < argc; i++) {
        mode_t mode;
        printf("%s: ", argv[i]);

        if (lstat(argv[i], &buf) < 0) {
            err_ret("lstat error: %s", argv[i]);
            continue;
        }

        mode = buf.st_mode;
        if (S_ISREG(mode)) {
            ptr = "regular";
        } else if (S_ISDIR(mode)) {
            ptr = "directory";
        } else if (S_ISCHR(mode)) {
            ptr = "character special";
        } else if (S_ISBLK(mode)) {
            ptr = "block special";
        } else if (S_ISFIFO(mode)) {
            ptr = "fifo";
        } else if (S_ISLNK(mode)) {
            ptr = "symbolic link";
        } else if (S_ISSOCK(mode)) {
            ptr = "socket";
        } else {
            ptr = "** unknown mode **";
        }
        printf("%s\n", ptr);
    }
    exit(0);
}
