#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



int
main(void)
{
    int tmp1 = fork();
    if (tmp1 == 0) {
        int tmp2 = fork();
        if (tmp2 == 0) {
            printf("%d ", 3);
            exit(0);
        }
        wait(NULL);
        printf("%d ", 2);
        exit(0);
    }
    wait(NULL);
    printf("%d\n", 1);
    return 0;
}
