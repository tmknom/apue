#include "apue.h"

int main(void) {
    daemonize("/bin/sh");
    for (;;) {
        sleep(10);
    }
}
