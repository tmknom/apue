#include "apue.h"
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>

#define BUFLEN 128
#define TIMEOUT 20

int connect_retry(int, int, int, const struct sockaddr *, socklen_t);

void sig_alrm(int sig) {
    printf("caught SIGALRM\n");
}

void print_uptime(int sockfd, struct addrinfo *aip) {
    int n;
    char buf[BUFLEN];

    buf[0] = 0;
    if (sendto(sockfd, buf, 1, 0, aip->ai_addr, aip->ai_addrlen) < 0)
        err_sys("sendto error");

    alarm(TIMEOUT);

    if ((n = recvfrom(sockfd, buf, BUFLEN, 0, NULL, NULL)) < 0) {
        if (errno != EINTR)
            alarm(0);
        err_sys("recvfrom error");
    }
    alarm(0);
    write(STDOUT_FILENO, buf, n);
}

int main(int argc, char *argv[]) {
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    int sockfd, err;
    struct sigaction sa;

    if (argc != 2)
        err_quit("invalid argument");

    sa.sa_handler = sig_alrm;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGALRM, &sa, NULL) < 0)
        err_sys("sigaction error");

    memset(&hint, 0, sizeof(hint));
    hint.ai_socktype = SOCK_DGRAM;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;

    if ((err = getaddrinfo(argv[1], "ruptime", &hint, &ailist)) != 0)
        err_quit("ruptimed: getaddrinfo error: %s", gai_strerror(err));

    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
        if ((sockfd = socket(aip->ai_family, SOCK_DGRAM, 0)) < 0) {
            err = errno;
        } else {
            print_uptime(sockfd, aip);
            exit(0);
        }
    }
    fprintf(stderr, "cannot contact %s: %s\n", argv[1], strerror(err));
    exit(1);
}

int connect_retry(int domain, int type, int protocol, const struct sockaddr *addr, socklen_t alen) {
    int fd, numsec;
    const int maxsleep = 2;

    for (numsec = 1; numsec <= maxsleep; numsec <<= 1) {
        errno = 0;

        if ((fd = socket(domain, type, protocol)) < 0) {
            err_ret("socket error");
            return (-1);
        }
        printf("succeed socket: fd = %d\n", fd);

        if (connect(fd, addr, alen) == 0) {
            return (fd); // 接続はacceptされた
        }

        err_ret("connect error");
        close(fd);

        // 再試行前に待つ
        if (numsec <= maxsleep / 2)
            sleep(numsec);
    }
    return (-1);
}
