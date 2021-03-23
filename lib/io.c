/*
 * 自前のIO関数
 */
#include "apue.h"
#include <errno.h>
#include <limits.h>
#include <fcntl.h>

#ifdef PATH_MAX
static long pathmax = PATH_MAX;
#else
static long pathmax = 0;
#endif

static long posix_version = 0;
static long xsi_version = 0;

/* PATH_MAXが不定であるとき／これが適切である保証はない */
#define PATH_MAX_GUESS 1024

/*
 * パス用領域の動的割り付け
 */
char *path_alloc(size_t *sizep) { // 非nullの場合には、sizepに確保したサイズが入る
    char *ptr;
    size_t size;

    if (posix_version == 0)
        posix_version = sysconf(_SC_VERSION);
    if (xsi_version == 0)
        xsi_version = sysconf(_SC_XOPEN_VERSION);

    if (pathmax == 0) {
        errno = 0;
        if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
            if (errno == 0)
                pathmax = PATH_MAX_GUESS; // 不定
            else
                err_sys("pathconf error for _PC_PATH_MAX");
        } else {
            pathmax++;
        }
    }

    // POSIX.1-2001より前では、PATH_MAXに終端のnullバイトが含まれる保証がない
    // XPG3でも同様
    if ((posix_version < 200112L) && (xsi_version < 4))
        size = pathmax + 1;
    else
        size = pathmax;

    if ((ptr = malloc(size)) == NULL)
        err_sys("malloc error for pathname");

    if (sizep != NULL)
        *sizep = size;

    return ptr;
}

/*
 * 指定したファイルディスクリプションのステータスフラグをオンにする
 */
void set_fl(int fd, int flags) {
    int val;

    if ((val = fcntl(fd, F_GETFD, 0)) < 0)
        err_sys("fcntl F_GETFD error");

    val |= flags; // フラグをオンにする

    if (fcntl(fd, F_SETFD, val) < 0)
        err_sys("fcntl F_SETFD error");
}

/*
 * 指定したファイルディスクリプションのステータスフラグをオフにする
 */
void clr_fl(int fd, int flags) {
    int val;

    if ((val = fcntl(fd, F_GETFD, 0)) < 0)
        err_sys("fcntl F_GETFD error");

    val &= ~flags; // フラグをオフにする

    if (fcntl(fd, F_SETFD, val) < 0)
        err_sys("fcntl F_SETFD error");
}

/*
 * ファイル全体にライトロック
 */
int lockfile(int fd) {
    struct flock fl;

    fl.l_type = F_WRLCK;
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;
    fl.l_len = 0;
    return (fcntl(fd, F_SETLK, &fl));
}
