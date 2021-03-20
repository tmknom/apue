#include "apue.h"

#define BSZ 48

int main(void) {
    char buf[BSZ];
    FILE *fp;

    memset(buf, 'a', BSZ - 2);
    buf[BSZ - 2] = '\0';
    buf[BSZ - 1] = 'X';

    if ((fp = fmemopen(buf, BSZ, "w+")) == NULL)
        err_sys("fmemopen error");

    printf("initial buffer content: %s\n", buf);

    fprintf(fp, "hello, world");
    printf("before flush: '%s'\n", buf);
    fflush(fp);
    printf("after flush: '%s'\n", buf);
    printf("len of string in buf = %ld\n", (long) strlen(buf));
    printf("\n");

    memset(buf, 'b', BSZ - 2);
    buf[BSZ - 2] = '\0';
    buf[BSZ - 1] = 'X';
    fprintf(fp, "hello, world");
    printf("before seek: '%s'\n", buf);
    fseek(fp, 0, SEEK_SET);
    printf("after seek: '%s'\n", buf);
    printf("len of string in buf = %ld\n", (long) strlen(buf));
    printf("\n");

    memset(buf, 'c', BSZ - 2);
    buf[BSZ - 2] = '\0';
    buf[BSZ - 1] = 'X';
    fprintf(fp, "hello, world");
    printf("before fclose: '%s'\n", buf);
    fclose(fp);
    printf("after fclose: '%s'\n", buf);
    printf("len of string in buf = %ld\n", (long) strlen(buf));

    exit(0);
}
