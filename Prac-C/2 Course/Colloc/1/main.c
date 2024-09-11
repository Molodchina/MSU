#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int
main(void)
{
    if (fork() == 0) {
        printf("%d %d\n", getppid(), getpid());
        exit(0);
    }
    if (fork() == 0) {
        printf("%d\n", getpid());
        exit(0);
    }
    return 0;
}
