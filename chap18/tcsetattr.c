#include "apue.h"
#include <termios.h>

int main(void) {
    struct termios term;
    long vdisable;

    if (isatty(STDIN_FILENO) == 0)
        err_quit("stdin is not a terminal device");

    if ((vdisable = fpathconf(STDIN_FILENO, _PC_VDISABLE)) < 0)
        err_quit("fpathconf error");

    if (tcgetattr(STDIN_FILENO, &term) < 0)
        err_sys("tcgetattr error");

    term.c_cc[VINTR] = vdisable; // INTR文字を無効にする
    term.c_cc[VEOF] = 2; // EOFはControl-B

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) < 0)
        err_sys("tcsetattr error");

    exit(0);
}
