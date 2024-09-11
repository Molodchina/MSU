#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>



int
main(void)
{
    int fd[2];
    pipe(fd);
    int pid = fork();
    if (pid < 0) {
        fprintf(stderr, "son create err\n");
        exit(1);
    } else if (pid == 0) {
        int pid2 = fork();
        if (pid2 < 0) {
            fprintf(stderr, "grandson create err\n");
            exit(1);
        } else if (pid2 == 0) {
            int tmp;
            long long sum = 0;
            close(fd[1]);
            while (read(fd[0], &tmp, sizeof(tmp)) > 0) {
                sum += tmp;
            }
            printf("%lld\n", sum); fflush(stdout);
            close(fd[0]);
            exit(0);
        } else {
            close(fd[0]);
            close(fd[1]);
            waitpid(pid2, NULL, 0);
            exit(0);
        }
    } else {
        int tmp;
        close(fd[0]);
        while (scanf("%d", &tmp) == 1) {
            write(fd[1], &tmp, sizeof(tmp));
        }
        close(fd[1]);
        waitpid(pid, NULL, 0);
        exit(0);
    }
}

