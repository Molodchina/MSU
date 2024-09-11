#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/signalfd.h>
#include <errno.h>
#include <stdlib.h>
#include <wait.h>


enum
{
    DEC_BASE = 10,
    FRST_SON = 1,
    SCND_SON = 2
};

int val = 0;

void
play (FILE *fin, FILE *fout, int num)
{
    const char stop_str[] = "STOP";
    sigset_t ss;
    pid_t tmp_pid;
    int tmp;

    sigemptyset(&ss);
    sigaddset(&ss, SIGUSR1);
    sigprocmask(SIG_SETMASK, &ss, NULL);

    while (1) {
        sigwaitinfo(&ss, NULL);
        if (fscanf(fin, "%d", &tmp_pid) < 0) {
            continue;
        }
        if (fscanf(fin, "%d", &tmp) < 0) {
            continue;
        }
        if (tmp == val) {
            fprintf(fout, "%s\n", stop_str);
            fflush(fout);
            kill(tmp_pid, SIGUSR1);
            _exit(0);
        }

        printf("%d %d\n", num, tmp);
        fflush(stdout);

        ++tmp;
        fprintf(fout, "%d\n%d\n", getpid(), tmp);
        fflush(fout);
        kill(tmp_pid, SIGUSR1);
    }
}

// FROM CHERNOV CONSULTATION

int main(int argc, char *argv[])
{
    if (argc <= 1) {
        fprintf(stderr, "arguments amount err\n");
        _exit(1);
    }

    const char done_str[] = "Done";
    sigset_t ss2;

    sigemptyset(&ss2);
    sigaddset(&ss2, SIGUSR1);
    sigprocmask(SIG_BLOCK, &ss2, NULL);

    char *eptr = NULL;
    errno = 0;
    long tmp_val = strtol(argv[1], &eptr, DEC_BASE);
    if (errno || *eptr || eptr == argv[1] ||
            (int) tmp_val != tmp_val || tmp_val <= 1) {
        printf("%s\n", done_str);
        fflush(stdout);
        _exit(0);
    }
    val = (int) tmp_val;

    int fd[2];
    pipe(fd);

    FILE *fin = fdopen(fd[0], "r");
    FILE *fout = fdopen(fd[1], "w");

    int pid1 = fork();
    if (pid1 < 0) {
        _exit(1);
    } else if (pid1 == 0) {
        play(fin, fout, 1);
        _exit(0);
    }
    int pid2 = fork();
    if (pid2 < 0) {
        _exit(1);
    } else if (pid2 == 0) {
        int tmp = 1;
        if (fprintf(fout, "%d\n%d\n", getpid(), tmp) < 0) {
            _exit(1);
        }
        fflush(fout);
        kill(pid1, SIGUSR1);

        play(fin, fout, 2);
        _exit(0);
    }

    while (wait(NULL) > 0) {}

    printf("%s\n", done_str);
    fflush(stdout);

    fclose(fin);
    fclose(fout);

    _exit(EXIT_SUCCESS);
}