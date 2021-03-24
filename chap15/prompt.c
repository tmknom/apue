#include "apue.h"
#include <sys/wait.h>

int main(void) {
    char line[MAXLINE];
    FILE *fpin;

    if ((fpin = popen("/work/bin/myuclc", "r")) == NULL)
        err_sys("cannot open myuclc");

    for (;;) {
        fputs("prompt> ", stdout);
        fflush(stdout);
        if (fgets(line, MAXLINE, fpin) == NULL) // パイプから読む
            break;
        if (fputs(line, stdout) == EOF)
            err_sys("fputs error to pipe");
    }

    if (pclose(fpin) == -1)
        err_sys("pclose error");
    putchar('\n');

    exit(0);
}
