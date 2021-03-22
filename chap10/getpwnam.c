#include "apue.h"
#include <pwd.h>

static void sig_alarm(int sig) {
    struct passwd *rootptr;

    printf("in signal handler\n");
    if ((rootptr = getpwnam("root")) == NULL)
        err_sys("getpwnam(root) error");
    if (strcmp(rootptr->pw_name, "root") != 0)
        printf("root return value corrupted!, pw_name = %s\n", rootptr->pw_name);

    alarm(1);
}

int main(void) {
    struct passwd *ptr;

    if (signal(SIGALRM, sig_alarm) == SIG_ERR)
        err_sys("signal error: SIGALRM");

    alarm(1);

    for (;;) {
        if ((ptr = getpwnam("docker")) == NULL)
            err_sys("getpwnam(root) error");
        if (strcmp(ptr->pw_name, "docker") != 0)
            printf("docker return value corrupted!, pw_name = %s\n", ptr->pw_name);
    }
}
