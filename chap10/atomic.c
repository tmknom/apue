#include "apue.h"

static volatile sig_atomic_t quitflag;

static void sig_int(int sig) {
    if (sig == SIGINT)
        printf("\ninterrupt\n");
    else if (sig == SIGQUIT)
        quitflag = 1;
}

int main(void) {
    sigset_t newmask, oldmask, zeromask;

    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("can't catch SIGINT");
    if (signal(SIGQUIT, sig_int) == SIG_ERR)
        err_sys("can't catch SIGQUIT");

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);

    // SIGQUITをブロックして現在のシグナルマスクを保存
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        err_sys("SIG_BLOCK error");

    while (quitflag == 0)
        sigsuspend(&zeromask);

    // SIGQUITを捕捉し、現在ブロックしている
    quitflag = 0;
    printf("\ncatch SIGQUIT\n");

    // SIGQUITをブロックしないシグナルマスクをセット
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        err_sys("SIG_SETMASK error");

    exit(0);
}
