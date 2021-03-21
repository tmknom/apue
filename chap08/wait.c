#include "apue.h"
#include <sys/wait.h>

int main(void) {
    int status;
    pid_t pid;

    printf("parent process: pid = %ld, ppid = %ld\n\n", (long) getpid(), (long) getppid());

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        printf("child process 1: pid = %ld, ppid = %ld\n", (long) getpid(), (long) getppid());
        exit(7);
    }

    printf("parent process wait: pid = %ld\n", (long) pid);
    if (wait(&status) != pid)
        err_sys("wait error");
    pr_exit(status);
    printf("\n");

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        printf("child process 2: pid = %ld, ppid = %ld\n", (long) getpid(), (long) getppid());
        abort(); // SIGABRT の生成
    }

    printf("parent process wait: pid = %ld\n", (long) pid);
    if (wait(&status) != pid)
        err_sys("wait error");
    pr_exit(status);
    printf("\n");

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        printf("child process 3: pid = %ld, ppid = %ld\n", (long) getpid(), (long) getppid());
        status /= 0; // ゼロ除算で SIGFPE の生成
    }

    printf("parent process wait: pid = %ld\n", (long) pid);
    if (wait(&status) != pid)
        err_sys("wait error");
    pr_exit(status);

    exit(0);
}
