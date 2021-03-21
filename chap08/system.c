#include "apue.h"
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int status;

    if ((status = system("date")) < 0)
        err_sys("system() error");
    pr_exit(status);

    if ((status = system("invalid")) < 0)
        err_sys("system() error");
    pr_exit(status);

    if ((status = system("whoami; exit 44")) < 0)
        err_sys("system() error");
    pr_exit(status);

    if (argc == 2) {
        if ((status = system(argv[1])) < 0)
            err_sys("system() error");
        pr_exit(status);
    }

    exit(0);
}
