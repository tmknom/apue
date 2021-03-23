#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>

#define COPYINCR (1024*1024)

int main(int argc, char *argv[]) {
    int fdin, fdout;
    void *src, *dst;
    size_t copysz;
    struct stat sbuf;
    off_t fsz = 0;

    if (argc != 3) {
        fprintf(stderr, "usage: %s fromfile tofile\n", argv[0]);
        exit(1);
    }

    if ((fdin = open(argv[1], O_RDONLY)) < 0)
        err_sys("open error: %s", argv[1]);
    if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
        err_sys("open error: %s", argv[2]);

    // 入力ファイルのサイズを取得
    if (fstat(fdin, &sbuf) < 0)
        err_sys("fstat error");

    // sh通力ファイルのサイズを設定
    if (ftruncate(fdout, sbuf.st_size) < 0)
        err_sys("fstat error");

    while (fsz < sbuf.st_size) {
        if ((sbuf.st_size - fsz) > COPYINCR)
            copysz = COPYINCR;
        else
            copysz = sbuf.st_size - fsz;

        if ((src = mmap(0, copysz, PROT_READ, MAP_SHARED, fdin, fsz)) == MAP_FAILED)
            err_sys("mmap error for input");
        if ((dst = mmap(0, copysz, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, fsz)) == MAP_FAILED)
            err_sys("mmap error for output");

        memcpy(dst, src, copysz);
        munmap(src, copysz);
        munmap(dst, copysz);
        fsz += copysz;
    }

    exit(0);
}
