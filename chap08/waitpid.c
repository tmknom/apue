#include "apue.h"
#include <sys/wait.h>

int main(void) {
    pid_t pid;

    printf("started parent process: pid = %ld, ppid = %ld\n\n", (long) getpid(), (long) getppid());

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) { // 子プロセス
        printf("forked first child process: pid = %ld, ppid = %ld\n", (long) getpid(), (long) getppid());
        fflush(NULL);

        if ((pid = fork()) < 0) {
            err_sys("fork error");
        } else if (pid > 0) { // 子プロセス
            sleep(1);
            printf("exit first child process: pid = %ld, ppid = %ld\n\n", (long) getpid(), (long) getppid());
            exit(0);
        }

        // 孫プロセス
        printf("forked second child process: pid = %ld, ppid = %ld\n", (long) getpid(), (long) getppid());
        fflush(NULL);
        sleep(3);
        printf("exit second child process: pid = %ld, ppid = %ld\n\n", (long) getpid(), (long) getppid());
        exit(0);
    }

    // 親プロセス
    printf("parent process waitpid for first child: pid = %ld\n", (long) pid);
    fflush(NULL);
    if (waitpid(pid, NULL, 0) != pid)
        err_sys("waitpid error");

    printf("exit parent process: pid = %ld, ppid = %ld\n", (long) getpid(), (long) getppid());
    exit(0);
}
