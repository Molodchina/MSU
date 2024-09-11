#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

void work(int rfd, int wfd, int serial)
{
    int v;

    read(rfd, &v, sizeof(v));
    printf("%d: %d\n", serial, v); fflush(stdout);
    ++v;
    write(wfd, &v, sizeof(v));
}

int main()
{
    int pid;

    mkfifo("p12", 0700);
    mkfifo("p21", 0700);

    if (!(pid = fork())) {
        int rfd = open("p12", O_RDONLY);
        int wfd = open("p21", O_WRONLY);
        // son
        while (1) {
            work(rfd, wfd, 2);
        }
    } else {
        int wfd = open("p12", O_WRONLY);
        int rfd = open("p21", O_RDONLY);
        // parent
        {
            int v = 1;
            write(wfd, &v, sizeof(v));
        }
        while (1) {
            work(rfd, wfd, 1);
        }
    }
}
