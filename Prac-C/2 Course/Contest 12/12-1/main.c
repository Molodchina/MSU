#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    if (argc != 5) {
        exit(1);
    }
    int pid = fork();
    int val = 0;
    if (pid == 0) {
        int fd1 = open(argv[2], O_RDONLY);
        int fd2 = open(argv[3], O_WRONLY | O_CREAT | O_APPEND, 0660);
        int fd3 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0660);
        if (fd1 < 0 || fd2 < 0 || fd3 < 0) {
            _exit(42);
        }
        dup2(fd1, 0);
        dup2(fd2, 1);
        dup2(fd3, 2);
        close(fd2);
        close(fd1);
        close(fd3);

        execlp(argv[1], argv[1], NULL);
        _exit(42);
    }

    wait(&val);
    printf("%d\n", val);
    return 0;
}
