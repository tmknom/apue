/*
 * 自前のデーモン関数
 */
#include "apue.h"
#include <sys/resource.h>
#include <syslog.h>
#include <fcntl.h>

/*
 * 自身をデーモン化
 */
void daemonize(const char *cmd) {
    int i, fd0, fd1, fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;

    // ファイル作成マスクをクリア
    umask(0);

    // ファイルディスクリプションの最大個数を取得
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
        err_quit("%s: cannot get file limit", cmd);

    // 制御端末から切断するためにセッションリーダになる
    if ((pid = fork()) < 0)
        err_quit("%s: cannot fork", cmd);
    else if (pid != 0)
        exit(0); // 親プロセスは終了する
    setsid(); // 新しいセッションを作成

    // 以降のオープンで制御端末を割り当てないようにする
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
        err_quit("%s: cannot ignore SIGHUP", cmd);
    if ((pid = fork()) < 0)
        err_quit("%s: cannot fork", cmd);
    else if (pid != 0)
        exit(0); // 親プロセスは終了する

    // カレントワーキングディレクトリをルートに変更し、
    // ファイルシステムのアンマウントを邪魔しない
    if (chdir("/") < 0)
        err_quit("%s: cannot chdir", cmd);

    // すべてのオープンしてあるファイルディスクリプションをクローズ
    if (rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for (i = 0; i < rl.rlim_max; ++i) {
        close(i);
    }

    // 標準入出力・標準エラー出力を/dev/nullに向ける
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    // ログファイルを初期化
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
        syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
        exit(1);
    }
}
