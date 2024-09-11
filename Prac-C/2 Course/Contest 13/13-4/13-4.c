#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

int k_fd[2];

void
handler(int sig)
{
    int tmp;
    close(k_fd[1]);
    while (read(k_fd[0], &tmp, sizeof(tmp)) > 0) {
        kill(tmp, SIGKILL);
    }
    while (wait(NULL) > 0) {}
    close(k_fd[0]);
    exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
    int fd[2] = { 0, 1 };
    sigaction(SIGUSR1, &(struct sigaction) { .sa_handler
            = handler, .sa_flags = SA_RESTART }, NULL);

    pipe(k_fd);

    for (int i = 1; i < argc; ++i) {
        int tmpfd[2] = { 0, 1 };
        if (i != argc - 1) {
            if (pipe2(tmpfd, O_CLOEXEC) < 0) {
                kill(getpid(), SIGUSR1);
                _exit(EXIT_FAILURE);
            }
        }
        int pid = fork();
        if (pid < 0) {
            kill(getpid(), SIGUSR1);
            _exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            close(k_fd[0]);
            int tmp_pid = getpid();
            write(k_fd[1], &tmp_pid, sizeof(tmp_pid));
            close(k_fd[1]);
            if (dup2(fd[0], STDIN_FILENO) < 0) {
                kill(getppid(), SIGUSR1);
                _exit(EXIT_FAILURE);
            }
            if (dup2(tmpfd[1], STDOUT_FILENO) < 0) {
                kill(getpid(), SIGUSR1);
                _exit(EXIT_FAILURE);
            }
            execlp(argv[i], argv[i], NULL);
            kill(getppid(), SIGUSR1);
            _exit(EXIT_FAILURE);
        }
        if (tmpfd[1] != 1) {
            close(tmpfd[1]);
        }
        if (fd[0] != 0) {
            close(fd[0]);
        }
        fd[0] = tmpfd[0];
    }
    while (wait(NULL) > 0) {}

    close(k_fd[0]);
    close(k_fd[1]);

    signal(SIGUSR1, SIG_DFL);
    exit(EXIT_SUCCESS);
}
