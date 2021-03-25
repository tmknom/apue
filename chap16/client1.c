#include "apue.h"
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>

#define BUFLEN 128

int connect_retry(int, int, int, const struct sockaddr *, socklen_t);

void print_uptime(int sockfd) {
    int n;
    char buf[BUFLEN];

    while ((n = recv(sockfd, buf, BUFLEN, 0)) > 0)
        write(STDOUT_FILENO, buf, n);

    if (n < 0)
        err_sys("recv error");
}

int main(int argc, char *argv[]) {
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    int sockfd, err;

    if (argc != 2)
        err_quit("invalid argument");

    memset(&hint, 0, sizeof(hint));
    hint.ai_flags = AI_CANONNAME;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;

    if ((err = getaddrinfo(argv[1], "ruptime", &hint, &ailist)) != 0)
        err_quit("ruptimed: getaddrinfo error: %s", gai_strerror(err));

    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
        if ((sockfd = connect_retry(aip->ai_family, SOCK_STREAM, 0, aip->ai_addr, aip->ai_addrlen)) < 0) {
            err = errno;
        } else {
            print_uptime(sockfd);
            exit(0);
        }
    }
    err_exit(err, "cannot connect to %s", argv[1]);
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
