#include "apue.h"

int main(void) {
    char name[L_tmpnam], line[MAXLINE];
    FILE *fp;

    printf("%s\n", tmpnam(NULL));

    tmpnam(name);
    printf("%s\n", name);

    if ((fp = tmpfile()) == NULL)
        err_sys("tmpfile error");

    if (fputs("one line of output\n", fp) == EOF)
        err_sys("fputs error");

    rewind(fp);

    if (fgets(line, sizeof(line), fp) == NULL)
        err_sys("fgets error");

    if (fputs(line, stdout) == EOF)
        err_sys("fputs stdout error");

    exit(0);
}
