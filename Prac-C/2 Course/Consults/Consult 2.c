#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/signalfd.h>

void work(int fd[2], int serial, int sfd)
{
    int v;

    struct signalfd_siginfo sss;
    read(sfd, &sss, sizeof(sss));
    read(fd[0], &v, sizeof(v));
    printf("%d: %d\n", serial, v); fflush(stdout);
    ++v;
    write(fd[1], &v, sizeof(v));
    kill(sss.ssi_pid, SIGUSR1);
}

int main()
{
    int fd[2];
    int pid;
    sigset_t ss1;

    sigemptyset(&ss1);
    sigaddset(&ss1, SIGUSR1);
    sigprocmask(SIG_BLOCK, &ss1, NULL);
    int sfd = signalfd(-1, &ss1, 0);

    pipe(fd);
    if (!(pid = fork())) {
        // son
        while (1) {
            work(fd, 2, sfd);
        }
    } else {
        // parent
        {
            int v = 1;
            write(fd[1], &v, sizeof(v));
        }
        kill(pid, SIGUSR1);
        while (1) {
            work(fd, 1, sfd);
        }
    }
}
