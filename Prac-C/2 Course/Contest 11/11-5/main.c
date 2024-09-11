#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int
main(void)
{
    int pid = fork();
    int val;
    if (pid < 0) {
        printf("%d\n", -1); fflush(stdout);
        return 0;
    } else if (pid == 0) {
        while(1) {
            if (scanf("%d", &val) != 1) {
                _exit(0);
            }
            int tmp_pid = fork();
            if (tmp_pid < 0) {
                printf("%d\n", -1); fflush(stdout);
                _exit(1);
            } else if (tmp_pid > 0) {
                int w_val = 0;
                wait(&w_val);
                if (WIFEXITED(w_val) && !WEXITSTATUS(w_val)) {
                    printf("%d\n", val); fflush(stdout);
                    _exit(0);
                } else {
                    _exit(1);
                }
            }
        }
    } else {
        wait(NULL);
    }
    return 0;
}

