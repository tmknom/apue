#include "apue.h"
#include <errno.h>
#include <time.h>

int main(void) {
    time_t t;
    struct tm *tmp;
    char buf1[16], buf2[64];

    errno = 0;

    time(&t);
    tmp = localtime(&t);

    if (strftime(buf1, 16, "time and date: %s, %a %b %d, %Y", tmp) == 0)
        err_msg("strftime: buffer length 16 is too small");
    else
        printf("%s\n", buf1);

    if (strftime(buf2, 64, "time and date: %s, %a %b %d, %Y", tmp) == 0)
        err_msg("strftime: buffer length 64 is too small");
    else
        printf("%s\n", buf2);

    exit(0);
}
