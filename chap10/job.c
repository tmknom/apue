#include "apue.h"

#define BUFFSIZE 1024

static void sig_tstp(int sig) {
    sigset_t mask;

    /* 端末モードをリセット */

    // SIGTSTPをアンブロック
    sigemptyset(&mask);
    sigaddset(&mask, SIGTSTP);
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    // デフォルト動作にリセット
    signal(SIGTSTP, SIG_DFL);

    // 自身にシグナルを贈る
    kill(getpid(), SIGTSTP);

    /* 再開するまでkillから戻らない */

    // シグナルハンドラを再確立
    signal(SIGTSTP, sig_tstp);

    /* 端末モードをリセット／スクリーンを再描画 */
}

int main(void) {
    int n;
    char buf[BUFFSIZE];

    // ジョブ制御シェルを使っているときにはSIGTSTPのみを捕捉
    if (signal(SIGTSTP, SIG_IGN) == SIG_DFL)
        signal(SIGTSTP, sig_tstp);

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
        if (write(STDOUT_FILENO, buf, n) != n)
            err_sys("write error");

    if (n < 0)
        err_sys("write error");

    exit(0);
}
