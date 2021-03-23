#include "apue.h"
#include <pthread.h>
#include <syslog.h>

sigset_t mask;

void reread(void) {
    syslog(LOG_INFO, "finished read config file");
}

void *thr_fn(void *arg) {
    int err, signo;

    for (;;) {
        err = sigwait(&mask, &signo);
        if (err != 0) {
            syslog(LOG_ERR, "sigwait error");
            exit(err);
        }

        switch (signo) {
            case SIGHUP:
                syslog(LOG_INFO, "Re-reading config file");
                reread();
                break;
            case SIGTERM:
                syslog(LOG_INFO, "got SIGTERM; exiting");
                exit(0);
            default:
                syslog(LOG_INFO, "unexpected signal %d\n", signo);
        }
    }
}

int main(int argc, char *argv[]) {
    int err;
    pthread_t tid;
    char *cmd;
    struct sigaction sa;

    if ((cmd = strrchr(argv[0], '/')) == NULL)
        cmd = argv[0];
    else
        cmd++;

    // デーモン化
    daemonize(cmd);

    // デーモンがひとつだけ動くことを保証
    if (already_running()) {
        syslog(LOG_ERR, "daemon already running");
        exit(0);
    }

    // SIGHUPをデフォルトに戻す
    // daemonize関数で一旦SIGHUPを無視しているのでそれを戻している
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
        err_quit("%s: cannot restore SIGHUP default");

    // すべてのシグナルをブロックする
    sigfillset(&mask);
    if ((err = pthread_sigmask(SIG_BLOCK, &mask, NULL)) != 0)
        err_exit(err, "SIG_BLOCK error");

    // SIGHUPとSIGTERMを受け取るスレッドの作成
    err = pthread_create(&tid, NULL, thr_fn, 0);
    if (err != 0)
        err_exit(err, "cannot create thread");

    /* デーモンの残りの処理 */

    exit(0);
}
