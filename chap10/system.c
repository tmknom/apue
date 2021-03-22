#include "apue.h"

static void sig_int(int sig) {
    printf("caught SIGINT\n");
}

static void sig_chld(int sig) {
    printf("caught SIGCHLD\n");
}

int main(void) {
    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("can't catch SIGINT");
    if (signal(SIGCHLD, sig_chld) == SIG_ERR)
        err_sys("can't catch SIGCHLD");

    if (system("/bin/ed") < 0)
        err_sys("system() error");

    exit(0);
}
