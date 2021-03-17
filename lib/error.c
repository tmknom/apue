/*
 * 自前のエラー関数
 */
#include "apue.h"
#include <errno.h> // errnoの定義
#include <stdarg.h> // ISO C可変長引数

/* errnoを出力するか切り替えるフラグ */
#define ENABLE_ERRNO 1
#define DISABLE_ERRNO !ENABLE_ERRNO

/* errnoが不要な場合に渡すダミー引数 */
#define NON_ERRNO 0

/* エラー関数内で共通利用する関数 */
static void err_doit(int, int, const char *, va_list);

/*
 * システムコールに関連の非致命的なエラー
 * メッセージを表示して戻る
 */
void err_ret(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_doit(ENABLE_ERRNO, errno, fmt, ap);
    va_end(ap);
}

/*
 * システムコール関連の致命的なエラー
 * メッセージを表示して終了
 */
void err_sys(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_doit(ENABLE_ERRNO, errno, fmt, ap);
    va_end(ap);
    exit(errno);
}

/*
 * システムコールに関連しない非致命的なエラー
 * エラーコードは明示的に引数で渡される
 * メッセージを表示して戻る
 */
void err_cont(int error, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_doit(ENABLE_ERRNO, error, fmt, ap);
    va_end(ap);
}

/*
 * システムコールに関連しない非致命的なエラー
 * エラーコードは明示的に引数で渡される
 * メッセージを表示して終了
 */
void err_exit(int error, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_doit(ENABLE_ERRNO, error, fmt, ap);
    va_end(ap);
    exit(error);
}

/*
 * システムコール関連の致命的なエラー
 * メッセージを表示し、コアダンプして終了
 */
void err_dump(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_doit(ENABLE_ERRNO, errno, fmt, ap);
    va_end(ap);
    abort();
    exit(1);
}

/*
 * システムコールに関連しない非致命的なエラー
 * メッセージを表示して戻る
 */
void err_msg(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_doit(DISABLE_ERRNO, NON_ERRNO, fmt, ap);
    va_end(ap);
}

/*
 * システムコールに関連しない致命的なエラー
 * メッセージを表示して終了
 */
void err_quit(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_doit(DISABLE_ERRNO, NON_ERRNO, fmt, ap);
    va_end(ap);
    exit(1);
}

/*
 * メッセージを表示して戻る
 * 呼び出し側がerrnoflagを指定
 */
static void err_doit(int errnoflag, int error, const char *fmt, va_list ap) {
    char buf[MAXLINE];
    vsnprintf(buf, MAXLINE - 1, fmt, ap);
    if (errnoflag == ENABLE_ERRNO) {
        snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1, ": %s", strerror(error));
    }
    strcat(buf, "\n");
    fflush(stdout); // stdoutとstderrが同じ場合
    fputs(buf, stderr);
    fflush(NULL); // すべての標準出力ストリームをフラッシュ
}
