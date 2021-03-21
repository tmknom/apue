#include "apue.h"
#include <sys/wait.h>

int main(void) {
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

    exit(0);
}
