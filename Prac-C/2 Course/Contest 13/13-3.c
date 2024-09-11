#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


enum
{
    CHMOD = 0611,
    READ_FLAG = 1,
    WRITE_FLAG = 2
};

int fd[2];

int
cmd(char *proc, char *file_in, char *file_out, int flag)
{
    int pid = fork();
    if (pid < 0) {
        exit(1);
    }
    else if (pid == 0) {
        if (file_in != NULL) {
            int fd_in = open(file_in, O_RDONLY);
            if (fd_in < 0) {
                exit(1);
            }
            dup2(fd_in, 0);
            close(fd_in);
        }
        if (file_out != NULL) {
            int fd_out = open(file_out, O_WRONLY | O_CREAT | O_APPEND, CHMOD);
            if (fd_out < 0) {
                exit(1);
            }
            dup2(fd_out, 1);
            close(fd_out);
        }
        if (flag) {
            if(flag && READ_FLAG) {
                dup2(fd[0], 0);
                close(fd[0]);
            }
            if(flag && WRITE_FLAG) {
                dup2(fd[1], 1);
                close(fd[1]);
            }
        }
        execlp(proc, proc, NULL);
        exit(1);
    }
    int val = 0;
    waitpid(pid, &val, 0);

    if (WIFEXITED(val) && !WEXITSTATUS(val)) {
        return 1;
    }
    return 0;
}

int
main(int argc, char *argv[])
{
    pipe(fd);
    if (argc < 5) {
        exit(1);
    }

    int pid = fork();
    if (pid < 0) {
        fprintf(stderr, "son create err\n");
        exit(1);
    } else if (pid == 0) {
        close(fd[0]);
        if (cmd(argv[1], argv[4], NULL, WRITE_FLAG) && cmd(argv[2], NULL, NULL, WRITE_FLAG)) {
            close(fd[1]);
            exit(0);
        }
        close(fd[1]);
        exit(1);
    } else {
        close(fd[1]);
        if (cmd(argv[3], NULL, argv[5], READ_FLAG)) {
            close(fd[0]);
            wait(NULL);
            exit(0);
        }

        close(fd[0]);
        wait(NULL);
        exit(0);
    }
}

