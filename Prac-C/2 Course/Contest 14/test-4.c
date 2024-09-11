#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int fd[2];
int pid;

void handler(int s)
{
    int v;
    read(fd[0], &v, sizeof(v));
    printf("%d %d\n", getpid(), v); fflush(stdout);
    ++v;
    write(fd[1], &v, sizeof(v));
    kill(pid, SIGUSR1);
}

int main()
{
    pipe(fd);
    sigaction(SIGUSR1, &(struct sigaction){ .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
    if (!(pid = fork())) {
        pid = getppid();
        while (1) pause();
    } else {
        {
            int v = 1;
            write(fd[1], &v, sizeof(v));
        }
        kill(pid, SIGUSR1);
        while (1) pause();
    }
}