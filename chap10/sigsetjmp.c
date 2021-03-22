#include "apue.h"
#include <errno.h>
#include <setjmp.h>
#include <time.h>

static void pr_mask(const char *str);

static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump;

static void sig_alarm(int sig) {
    pr_mask("in sig_alarm: ");
}

static void sig_usr1(int sig) {
    time_t starttime;

    if (canjump == 0)
        return;

    pr_mask("stating sig_usr1: ");

    alarm(3);
    starttime = time(NULL);

    // 5秒間ビジーウェイト
    for (;;) {
        if (time(NULL) > starttime + 5)
            break;
    }

    pr_mask("finishing sig_usr1: ");

    canjump = 0;
    siglongjmp(jmpbuf, 1); // mainにジャンプしてreturnしない
}

int main(void) {
    if (signal(SIGUSR1, sig_usr1) == SIG_ERR)
        err_sys("can't catch SIGUSR1");
    if (signal(SIGALRM, sig_alarm) == SIG_ERR)
        err_sys("can't catch SIGALRM");

    pr_mask("stating main: ");
    if (sigsetjmp(jmpbuf, 1)) {
        pr_mask("ending main: ");
        exit(0);
    }

    canjump = 1;// ここでsigsetjumpはOK
    printf("can sigsetjump\n");

    for (;;) {
        pause();
    }
}

static void pr_mask(const char *str) {
    sigset_t sigset;
    int errno_save;

    errno_save = errno;
    if (sigprocmask(0, NULL, &sigset) < 0) {
        err_ret("sigprocmask error");
    } else {
        printf("%s", str);
        if (sigismember(&sigset, SIGINT))
            printf(" SIGINT");
        if (sigismember(&sigset, SIGQUIT))
            printf(" SIGQUIT");
        if (sigismember(&sigset, SIGUSR1))
            printf(" SIGUSR1");
        if (sigismember(&sigset, SIGALRM))
            printf(" SIGALRM");
        printf("\n");
    }
    errno = errno_save;
}
