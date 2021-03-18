#include "apue.h"
#include <fcntl.h>

#define BUFFSIZE 4096

static void set_fl(int, int);

int main(void) {
    int n;
    char buf[BUFFSIZE];

    set_fl(STDOUT_FILENO, O_SYNC);

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            err_sys("write error");
        }
    }

    if (n < 0)
        err_sys("read error");

    exit(0);
}

static void set_fl(int fd, int flags) {
    int val;

    if ((val = fcntl(fd, F_GETFD, 0)) < 0)
        err_sys("fcntl F_GETFD error");

    val |= flags; // フラグをオンにする

    if (fcntl(fd, F_SETFD, val) < 0)
        err_sys("fcntl F_SETFD error");
}
