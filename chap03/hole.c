#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void) {
    int fd;

    if ((fd = creat("file.hole.o", S_IWUSR)) < 0)
        err_sys("creat error");

    if (write(fd, buf1, 10) != 10)
        err_sys("buf1 write error");
    /* オフセットはここで 10 */

    if (lseek(fd, 16384, SEEK_SET) == -1)
        printf("cannot seek\n");
    /* オフセットはここで 16384 */

    if (write(fd, buf2, 10) != 10)
        err_sys("buf2 write error");
    /* オフセットはここで 16394 */

    exit(0);
}
