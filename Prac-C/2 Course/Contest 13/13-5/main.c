#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>

enum
{
    DEC_BASE = 10,
    START_POINT = 1
};

int val = 0;

void
play (FILE *fin, FILE *fout, int num)
{
    const char stop_str[] = "STOP";
    int tmp;

    while (fscanf(fin, "%d", &tmp) > 0) {
        printf("%d %d\n", num, tmp);
        fflush(stdout);

        // write
        ++tmp;
        if (tmp == val) {
            fprintf(fout, "%s\n", stop_str);
            fflush(fout);
            _exit(0);
        }

        fprintf(fout, "%d\n", tmp);
        fflush(fout);
    }
    _exit(0);
}


int
main(int argc, char *argv[])
{
    if (argc <= 1) {
        fprintf(stderr, "arguments amount err\n");
        _exit(1);
    }
    const char done_str[] = "Done";

    char *eptr = NULL;
    errno = 0;
    long tmp_val = strtol(argv[1], &eptr, DEC_BASE);
    if (errno || *eptr || eptr == argv[1]
            || (int) tmp_val != tmp_val || tmp_val <= 1) {
        printf("%s\n", done_str);
        fflush(stdout);

        exit(EXIT_SUCCESS);
    }
    val = (int) tmp_val;

    int fd1[2];
    int fd2[2];
    if (pipe(fd1) < 0) {
        fprintf(stderr, "1 pipe create err\n");
        _exit(1);
    }
    if (pipe(fd2) < 0) {
        fprintf(stderr, "2 pipe create err\n");
        _exit(1);
    }

    FILE *fin1 = fdopen(fd1[0], "r");
    FILE *fout1 = fdopen(fd1[1], "w");
    FILE *fin2 = fdopen(fd2[0], "r");
    FILE *fout2 = fdopen(fd2[1], "w");


    // son 1
    int pid1 = fork();
    if (pid1 < 0) {
        fprintf(stderr, "1 son err\n");
        _exit(1);
    } else if (pid1 == 0) {
        play(fin1, fout2, 1);
    }

    int pid2 = fork();
    if (pid2 < 0) {
        fprintf(stderr, "2 son err\n");
        _exit(1);
    } else if (pid2 == 0) {
        int tmp = 1;
        if (fprintf(fout1, "%d\n", tmp) < 0) {
            _exit(1);
        }
        fflush(fout1);

        play(fin2, fout1, 2);
        _exit(0);
    }


    // FATHER
    while (wait(NULL) > 0) {}

    fclose(fin1);
    fclose(fin2);
    fclose(fout1);
    fclose(fout2);

    printf("%s\n", done_str);
    fflush(stdout);

    exit(EXIT_SUCCESS);
}
