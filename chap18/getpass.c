#include "apue.h"
#include <termios.h>
#include <pwd.h>

int main(void) {
    char *ptr;

    if ((ptr = getpass("Enter password:")) == NULL)
        err_sys("getpass error");
    printf("password: %s\n", ptr);

    /* パスワードを使った処理（暗号化など） */
    while (*ptr != 0)
        *ptr++ = 0;

    exit(0);
}
