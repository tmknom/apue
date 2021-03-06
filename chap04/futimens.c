#include "apue.h"
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int i, fd;
    struct stat statbuf;
    struct timespec times[2];

    for (i = 1; i < argc; ++i) {
        if (stat(argv[i], &statbuf) < 0) {
            err_ret("stat error: %s", argv[i]);
            continue;
        }

        if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) {
            err_ret("open error: %s", argv[i]);
            continue;
        }

        times[0].tv_sec = statbuf.st_atime;
        times[0].tv_nsec = 0;
        times[1].tv_sec = statbuf.st_mtime;
        times[1].tv_nsec = 0;

        if (futimens(fd, times) < 0)
            err_ret("futimens error: %s", argv[i]);

        close(fd);
    }
    exit(0);
}
