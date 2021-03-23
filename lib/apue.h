/*
 * 自前のヘッダ
 *
 * 標準システムヘッダの前に取り込むこと
 */
#ifndef _APUE_H
#define _APUE_H

/*
 * よく使う標準システムヘッダ
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
 * 一行の最大長
 */
#define MAXLINE 4096

/*
 * IO関数のプロトタイプ
 */
char *path_alloc(size_t *sizep);

void set_fl(int, int);

void clr_fl(int, int);

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len);

pid_t lock_test(int fd, int type, off_t offset, int whence, off_t len);

int lockfile(int fd);

/*
 * プロセス関数のプロトタイプ
 */
void pr_exit(int status);

int system(const char *cmdstring);

/*
 * デーモン関数のプロトタイプ
 */
void daemonize(const char *cmd);

int already_running(void);

/*
 * エラー関数のプロトタイプ
 *
 * __attribute__：関数属性の定義
 * noreturn：コンパイラに対して関数が戻らないことを知らせる最適化オプション
 */
void err_ret(const char *, ...);

void err_sys(const char *, ...) __attribute__((noreturn));

void err_cont(int, const char *, ...);

void err_exit(int, const char *, ...) __attribute__((noreturn));

void err_dump(const char *, ...) __attribute__((noreturn));

void err_msg(const char *, ...);

void err_quit(const char *, ...) __attribute__((noreturn));

#endif /* _APUE_H */
