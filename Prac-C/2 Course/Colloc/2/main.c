#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int
main(void)
{
    int fd[2];
    pipe(fd);
    char x[] = "01\n";

    if (fork()) {
        puts(x + 1);
        write(fd[1], x, 1);
        printf("DONE_FATHER: %c\n", *x);
        wait(NULL);
    } else {
        write(fd[1], &x[1], 1);
        printf("DONE_SON: %c\n", x[1]);
        read(fd[0], x, 1);
        printf("DONE_SON 1: %s\n", x);
        read(fd[0], x + 1, 1);
        printf("DONE_SON 2: %s\n", x);
    }
    printf("DONE_END\n");
    puts(x);

    return 0;
}
