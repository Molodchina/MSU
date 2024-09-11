#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/signalfd.h>
#include <stdlib.h>
#include <wait.h>
#include <fcntl.h>



int main(int argc, char *argv[])
{
    if (argc <= 1) {
        fprintf(stderr, "arguments amount err\n");
        _exit(1);
    }

    sigset_t ss;
    siginfo_t info;
    size_t offset = 0;

    sigemptyset(&ss);
    sigaddset(&ss, SIGUSR1);
    sigaddset(&ss, SIGUSR2);
    sigaddset(&ss, SIGIO);
    sigaddset(&ss, SIGALRM);
    sigprocmask(SIG_BLOCK, &ss, NULL);

    int pid1 = fork();
    if (pid1 < 0) {
        _exit(1);
    } else if (pid1 == 0) {
        sigset_t ss1;
        siginfo_t info1;
        unsigned char res = 0;
        offset = 0;

        sigemptyset(&ss1);
        sigaddset(&ss1, SIGUSR1);
        sigaddset(&ss1, SIGUSR2);
        sigaddset(&ss1, SIGIO);
        sigprocmask(SIG_SETMASK, &ss1, NULL);

        while (1) {
            sigwaitinfo(&ss1, &info1);

            if (info1.si_signo == SIGUSR1) {
                ++offset;
            } else if (info1.si_signo == SIGUSR2) {
                res += 1<<offset;
                ++offset;
            } else if (info1.si_signo == SIGIO) {
                _exit(0);
            }
            if (offset == __CHAR_BIT__) {
                printf("%c", res);
                fflush(stdout);
                offset = 0;
                res = 0;
            }

            kill(getppid(), SIGALRM);
        }
        _exit(0);
    }

    int pid2 = fork();
    if (pid2 < 0) {
        _exit(1);
    } else if (pid2 == 0) {
        sigset_t ss2;

        sigemptyset(&ss2);
        sigaddset(&ss2, SIGALRM);
        sigprocmask(SIG_SETMASK, &ss2, NULL);

        unsigned char val;
        offset = 0;
        int rfd = open(argv[1], O_RDONLY);

        while (1) {
            if (read(rfd, &val, sizeof(val)) <= 0) {
                close(rfd);
                kill(getppid(), SIGIO);
                _exit(0);
            }

            for (int i = 0; i < __CHAR_BIT__; ++i) {
                if (val&(1<<offset)) {
                    kill(getppid(), SIGUSR2);
                } else {
                    kill(getppid(), SIGUSR1);
                }
                sigwaitinfo(&ss2, NULL);
                ++offset;
                if (offset == __CHAR_BIT__) {
                    offset = 0;
                }
            }
        }
        _exit(0);
    }

    while (1) {
        sigwaitinfo(&ss, &info);
        if (info.si_signo == SIGALRM) {
            kill(pid2, SIGALRM);
        } else if (info.si_signo == SIGUSR1 || info.si_signo == SIGUSR2) {
            kill(pid1, info.si_signo);
        } else if (info.si_signo == SIGIO) {
            kill(pid1, info.si_signo);
            break;
        }
    }

    while (wait(NULL) > 0) {}

    _exit(EXIT_SUCCESS);
}