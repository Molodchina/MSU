#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


enum
{
    SUCCES_EXEC = 's',
    PARAL_EXEC = 'p'
};


int
main(int argc, char *argv[])
{
    int success_progs = 0;
    for (int prog_num = 1; prog_num < argc; ++prog_num) {
        char exec_mode = argv[prog_num][0];
        if (exec_mode == PARAL_EXEC) {
            char *tmp_prog = NULL;
            int pid = fork();
            if (pid < 0) {
                _exit(1);
            }
            else if (pid == 0) {
                tmp_prog = calloc(strlen(argv[prog_num]) - 1, sizeof(*tmp_prog));
                for (int j = 1; j < strlen(argv[prog_num]); ++j) {
                    tmp_prog[j - 1] = argv[prog_num][j];
                }
                execlp(tmp_prog, tmp_prog, NULL);
                _exit(1);
            }
            free(tmp_prog);
        } else if (exec_mode == SUCCES_EXEC) {
            char *tmp_prog = NULL;

            int val = 0;
            while (wait(&val) > 0) {
                if (WIFEXITED(val) && !WEXITSTATUS(val)) {
                    ++success_progs;
                }
            }

            int pid = fork();
            if (pid < 0) {
                _exit(1);
            }
            else if (pid == 0) {
                tmp_prog = calloc(strlen(argv[prog_num]) - 1, sizeof(*tmp_prog));
                for (int j = 1; j < strlen(argv[prog_num]); ++j) {
                    tmp_prog[j - 1] = argv[prog_num][j];
                }
                execlp(tmp_prog, tmp_prog, NULL);
                _exit(1);
            }
            free(tmp_prog);
        }
    }

    int val = 0;
    while (wait(&val) > 0) {
        if (WIFEXITED(val) && !WEXITSTATUS(val)) {
            ++success_progs;
        }
    }

    printf("%d\n", success_progs);
    exit(0);
}
