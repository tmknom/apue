#include "apue.h"
#include <termios.h>

int isatty(int fd) {
    struct termios ts;
    return (tcgetattr(fd, &ts) != -1);
}

void print_ttyname(int fd) {
    char *name;
    if (isatty(fd)) {
        name = ttyname(fd);
        if (name == NULL)
            name = "undefined";
    } else {
        name = "not a tty";
    }
    printf("fd %d: %s\n", fd, name);
}

int main(void) {
    print_ttyname(STDIN_FILENO);
    print_ttyname(STDOUT_FILENO);
    print_ttyname(STDERR_FILENO);

    exit(0);
}
