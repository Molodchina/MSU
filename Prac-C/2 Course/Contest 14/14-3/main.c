#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>


enum
{
    DEC_BASE = 10
};


int
main(int argc, char *argv[])
{
    int success_progs = 0;
    char *eptr = NULL;
    errno = 0;
    long tmp = strtol(argv[1], &eptr, DEC_BASE);
    if (errno || *eptr || eptr == argv[1] || (int) tmp != tmp) {
        exit(1);
    }
    int paral_num = (int) tmp;

    for (int i = 2; i < argc && i < paral_num + 2; ++i) {
        int pid = fork();
        if (pid < 0) {
            _exit(1);
        }
        else if (pid == 0) {
            char prog[PATH_MAX] = {};
            int file = open(argv[i], O_RDONLY);
            size_t pos = 0;
            char symb;
            while (read(file, &symb, sizeof(symb)) > 0) {
                if (symb == ' ' || symb == '\n'
                        || symb == '\0' || symb == EOF) {
                    break;
                }
                prog[pos++] = symb;
            }
            execlp(prog, prog, NULL);
            _exit(1);
        }
    }

    int val;
    while (wait(&val) > 0) {
        if (WIFEXITED(val) && !WEXITSTATUS(val)) {
            ++success_progs;
        }
    }

    for (int i = paral_num + 2; i < argc; ++i) {
        int pid = fork();
        if (pid < 0) {
            _exit(1);
        }
        else if (pid == 0) {
            char prog[PATH_MAX] = {};
            int file = open(argv[i], O_RDONLY);
            size_t pos = 0;
            char symb;
            while (read(file, &symb, sizeof(symb)) > 0) {
                if (symb == ' ' || symb == '\n'
                        || symb == '\0' || symb == EOF) {
                    break;
                }
                prog[pos++] = symb;
            }
            execlp(prog, prog, NULL);
            _exit(1);
        }
        waitpid(pid, &val, 0);
        if (WIFEXITED(val) && !WEXITSTATUS(val)) {
            ++success_progs;
        }
    }

    printf("%d\n", success_progs);
    exit(0);
}