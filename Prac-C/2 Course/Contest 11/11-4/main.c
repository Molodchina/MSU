#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int
main(void)
{
    unsigned long n;
    scanf("%lu", &n);
    
    for (unsigned long i = 1; i <= n; ++i) {
        int pid_tmp = fork();
        if (pid_tmp == 0) {
            printf("%lu", i); fflush(stdout);
            if (i != n) {
                printf(" "); fflush(stdout);
            } else {
                printf("\n"); fflush(stdout);
            }
            _exit(0);
        } else if (pid_tmp == 1) {
            wait(NULL);
        }
    }

    return 0;
}
