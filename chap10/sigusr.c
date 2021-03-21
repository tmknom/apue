#include "apue.h"
#include <errno.h>

static void sig_usr(int sig) {
    if (sig == SIGUSR1) {
        printf("received SIGUSR1\n");
    } else if (sig == SIGUSR2) {
        printf("received SIGUSR2\n");
    } else {
        err_dump("received signal %d\n", sig);
    }
}

int main(void) {
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
        err_sys("signal error: SIGUSR1");
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
        err_sys("signal error: SIGUSR2");

    for (;;) {
        pause();
    }
}
