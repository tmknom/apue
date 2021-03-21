#include "apue.h"

int globvar = 6;
char buf[] = "a write to stdout\n";

int main(void) {
    int var;
    pid_t pid;

    var = 88;
    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
        err_sys("write error");
    printf("before fork\n"); // 標準出力はフラッシュしない

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        // 子プロセス
        globvar++;
        var++;
    } else {
        // 親プロセス
        sleep(2);
    }

    printf("pid = %ld, ppid = %ld, glob = %d, var = %d\n", (long) getpid(), (long) getppid(), globvar, var);
    exit(0);
}
