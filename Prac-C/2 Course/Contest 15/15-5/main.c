#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/signalfd.h>
#include <errno.h>

// From Chernov Consult

enum
{
    DEC_BASE = 10,
    BLOCK_SIZE = 21,
    BUF_SIZE = 16
};

int64_t
getval (char *str)
{
    char *eptr = NULL;
    errno = 0;
    long long tmp = strtoll(str, &eptr, DEC_BASE);
    return ((int64_t) tmp);
}

int main(int argc, char *argv[])
{
    int nf = argc - 1;
    int fds[BLOCK_SIZE];
    long long sum[BLOCK_SIZE] = {};
    char buf[BUF_SIZE];
    int cur = -1;

    for (int i = 0; i < nf; ++i) {
        fds[i] = open(argv[i + 1], O_RDONLY, 0);
    }

    sigset_t ss;
    sigemptyset(&ss);
    sigaddset(&ss, SIGTERM);
    for (int i = 0; i < nf; ++i) {
        sigaddset(&ss, SIGRTMIN + i);
    }
    sigprocmask(SIG_BLOCK, &ss, NULL);
    int sfd = signalfd(-1, &ss, 0);

    printf("%d\n", getpid()); fflush(stdout);

    while (1) {
        fd_set rfd;
        FD_ZERO(&rfd);
        int maxfd = sfd;
        FD_SET(sfd, &rfd);
        if (cur >= 0) {
            FD_SET(fds[cur], &rfd);
            if (fds[cur] > maxfd) {
                maxfd = fds[cur];
            }
        }

        pselect(maxfd + 1, &rfd, NULL, NULL, NULL, NULL);

        if (cur >= 0 && FD_ISSET(fds[cur], &rfd)) {
            if (fds[cur] < 0) {
                cur = -1;
            }
            int r = read(fds[cur], buf, BUF_SIZE);
            if (r == 0) {
                close(fds[cur]);
                fds[cur] = -1;
                cur = -1;
            } else {
                sum[cur] += (long long) getval(buf);
            }
        } else if (FD_ISSET(sfd, &rfd)) {
            struct signalfd_siginfo tmp_sig;
            read(sfd, &tmp_sig, sizeof(tmp_sig));
            if (tmp_sig.ssi_signo == SIGTERM) {
                break;
            } else if (tmp_sig.ssi_signo >= SIGRTMIN
                    && tmp_sig.ssi_signo < SIGRTMIN + BLOCK_SIZE) {
                cur = (int) tmp_sig.ssi_signo - SIGRTMIN;
            }
        }
    }

    for (int i = 0; i < nf; ++i) {
        printf("%lld\n", sum[i]);
        fflush(stdout);
        if (fds[i] != -1) {
            close(fds[i]);
        }
    }
    close(sfd);

    exit(EXIT_SUCCESS);
}