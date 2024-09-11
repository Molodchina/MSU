#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <fcntl.h>

int
main()
{
    pid_t pid;
    int fd[2];
    int x = 3;

    pipe(fd);
    if ( (pid = fork()) > 0) {
        printf("FATHER: %d\n", x);

        x = 777;
        write(fd[1], &x, sizeof(x));

        //kill(pid, SIGKILL);
        wait(NULL);
    } else {
        wait(NULL);
        read(fd[0], &x, 4);
        printf("SON: %d\n", x);

        ++x;
        write(fd[1], &x, sizeof(x));

        //kill(getpid(), SIGKILL);
    }
    printf("OUT: %d\n", x);
    return 0;
}
