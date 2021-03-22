/*
 * 自前のプロセス関数
 */
#include "apue.h"
#include <sys/wait.h>
#include <errno.h>

/*
 * プロセスの終了状態の表示
 */
void pr_exit(int status) {
    if (WIFEXITED(status)) {
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("abnormal termination, signal number = %d%s\n",
               WTERMSIG(status),
#ifdef WCOREDUMP
                WCOREDUMP(status) ? " (core file generated)" : "");
#else
               "");
#endif
    } else if (WIFSTOPPED(status)) {
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
    }
}

/*
 * プロセス内からコマンドを実行
 */
int system(const char *cmdstring) {
    pid_t pid;
    int status;
    struct sigaction ignore, saveintr, savequit;
    sigset_t chldmask, savemask;

    if (cmdstring == NULL)
        return (1);

    // SIGINTとSIGQUITを無視する
    ignore.sa_handler = SIG_IGN;
    sigemptyset(&ignore.sa_mask);
    ignore.sa_flags = 0;
    if (sigaction(SIGINT, &ignore, &saveintr) < 0)
        return (-1);
    if (sigaction(SIGQUIT, &ignore, &savequit) < 0)
        return (-1);

    // SIGCHLDをブロックする
    sigemptyset(&chldmask);
    sigaddset(&chldmask, SIGCHLD);
    if (sigprocmask(SIG_BLOCK, &chldmask, &savemask) < 0)
        return (-1);

    if ((pid = fork()) < 0) {
        status = -1;
    } else if (pid == 0) {
        // 子プロセスのシグナルマスクをリセット
        sigaction(SIGINT, &saveintr, NULL);
        sigaction(SIGQUIT, &savequit, NULL);
        sigprocmask(SIG_SETMASK, &savemask, NULL);

        // コマンドの実行
        execl("/bin/sh", "sh", "-c", cmdstring, (char *) 0);
        _exit(127); // execlエラー
    } else {
        while (waitpid(pid, &status, 0) < 0) {
            if (errno != EINTR) {
                status = -1; // waitpidでEINTR以外のエラー
                break;
            }
        }
    }

    // 親プロセスのシグナルマスクをリセット
    if (sigaction(SIGINT, &saveintr, NULL) < 0)
        return (-1);
    if (sigaction(SIGQUIT, &savequit, NULL) < 0)
        return (-1);
    if (sigprocmask(SIG_SETMASK, &savemask, NULL) < 0)
        return (-1);

    return (status);
}
