#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int
cmd(char *proc)
{
    int pid = fork();
    if (pid < 0) {
        exit(1);
    }
    else if (pid == 0) {
        execlp(proc, proc, NULL);
        exit(1);
    }
    int val = 0;
    wait(&val);

    if (WIFEXITED(val) && !WEXITSTATUS(val)) {
        return 1;
    }
    return 0;
}

int
main(int argc, char *argv[])
{
    if (argc < 3) {
        exit(1);
    }

    if ((cmd(argv[1]) || cmd(argv[2])) && cmd(argv[3])) {
        exit(0);
    }
    else {
        exit (1);
    }
}
