#include "apue.h"
#include <sys/wait.h>

#define DEF_PAGER "/usr/bin/less"

int main(int argc, char *argv[]) {
    int n;
    int fd[2];
    pid_t pid;
    char *pager, *argv0;
    char line[MAXLINE];
    FILE *fp;

    if (argc != 2)
        err_quit("usage: %s <pathname>\n", argv[0]);

    if ((fp = fopen(argv[1], "r")) == NULL)
        err_sys("cannot open %s", argv[1]);
    if (pipe(fd) < 0)
        err_sys("pipe error");

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) {
        // 親プロセス
        close(fd[0]); // 読み取り側をクローズ

        // argv[1]をパイプへコピー
        while (fgets(line, MAXLINE, fp) != NULL) {
            n = strlen(line);
            if (write(fd[1], line, n) != n)
                err_sys("write error to pipe");
        }
        if (ferror(fp))
            err_sys("fgets error");

        close(fd[1]); // 読み手側の書き出し端点をクローズ

        if (waitpid(pid, NULL, 0) < 0)
            err_sys("waitpid error");
        exit(0);
    } else {
        // 子プロセス
        close(fd[1]); // 書き込み側をクローズ
        if (fd[0] != STDIN_FILENO) {
            if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
                err_sys("dup2 error");
            close(fd[0]); // dup2のあとでこれは必要ない
        }

        if ((pager = getenv("PAGER")) == NULL)
            pager = DEF_PAGER;

        if ((argv0 = strrchr(pager, '/')) != NULL)
            argv0++;
        else
            argv0 = pager;

        if (execl(pager, argv0, (char *) 0) < 0)
            err_sys("execl error for %s", pager);
    }

    exit(0);
}
