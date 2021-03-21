#include "apue.h"
#include <sys/times.h>

static void pr_times(clock_t, struct tms *, struct tms *);

static void do_cmd(char *);

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);
    for (int i = 1; i < argc; ++i) {
        do_cmd(argv[i]);
    }
    exit(0);
}

static void do_cmd(char *cmd) {
    struct tms start, end;
    clock_t startc, endc;
    int status;

    printf("\ncommand: %s\n", cmd);

    if ((startc = times(&start)) == -1)
        err_sys("times error");

    if ((status = system(cmd)) < 0)
        err_sys("system error");

    if ((endc = times(&end)) == -1)
        err_sys("times error");

    pr_times(endc - startc, &start, &end);
    pr_exit(status);
}

static void pr_times(clock_t real, struct tms *start, struct tms *end) {
    static long clktck = 0;
    if (clktck == 0)
        if ((clktck = sysconf(_SC_CLK_TCK)) < 0)
            err_sys("sysconf error");

    printf("  real:\t%7.2f\n", real / (double) clktck);
    printf("  user:\t%7.2f\n", (end->tms_utime - start->tms_utime) / (double) clktck);
    printf("  sys:\t%7.2f\n", (end->tms_stime - start->tms_stime) / (double) clktck);
    printf("  child user:\t%7.2f\n", (end->tms_cutime - start->tms_cutime) / (double) clktck);
    printf("  child sys:\t%7.2f\n", (end->tms_cstime - start->tms_cstime) / (double) clktck);
}
