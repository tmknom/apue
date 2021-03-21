#include "apue.h"
#include <sys/wait.h>

char *env_list[] = {"USER=unknown", "PATH=/tmp", NULL};

int main(void) {
    pid_t pid;

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        if (execle("/work/bin/echoall", "echoall", "myarg1", "MY ARG2", (char *) 0, env_list) < 0)
            err_sys("execle error");
    }

    if (waitpid(pid, NULL, 0) < 0)
        err_sys("wait error");

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        if (execlp("/work/bin/echoall", "echoall", "only 1 arg", (char *) 0) < 0)
            err_sys("execle error");
    }

    exit(0);
}
