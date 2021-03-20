#include "apue.h"
#include <setjmp.h>

void f1(int, int, int, int);

void f2(void);

static jmp_buf jmpbuffer;
static int globalval;

int main(void) {
    int autoval;
    register int registerval;
    volatile int volatileval;
    static int staticval;

    globalval = 1;
    autoval = 2;
    registerval = 3;
    volatileval = 4;
    staticval = 5;

    if (setjmp(jmpbuffer) != 0) {
        printf("after longjmp: \n");
        printf("global=%d, auto=%d, register=%d, volatile=%d, static~%d\n",
               globalval, autoval, registerval, volatileval, staticval);
        exit(0);
    }

    globalval = 91;
    autoval = 92;
    registerval = 93;
    volatileval = 94;
    staticval = 95;

    f1(autoval, registerval, volatileval, staticval);
    exit(0);
}

void f1(int autoval, int registerval, int volatileval, int staticval) {
    printf("in f1(): \n");
    printf("global=%d, auto=%d, register=%d, volatile=%d, static~%d\n",
           globalval, autoval, registerval, volatileval, staticval);
    f2();
}

void f2(void) {
    longjmp(jmpbuffer, 1);
}
