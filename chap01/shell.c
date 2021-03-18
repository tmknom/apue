#include "apue.h"
#include <sys/wait.h>

int main(void) {
    int status;
    char buf[MAXLINE];
    pid_t pid;

    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = 0; // 改行文字をnullに置換
        }

        if ((pid = fork()) < 0) {
            err_sys("fork error");
        } else if (pid == 0) { // 子プロセス
            execlp(buf, buf, (char *) 0);
            err_ret("couldn't execute: %s", buf);
            exit(127);
        }

        if ((pid = waitpid(pid, &status, 0)) < 0) {// 親プロセス
            err_sys("waitpid error");
        }
        printf("%% ");
    }
    exit(0);
}
