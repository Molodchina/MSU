#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

enum
{
    MAX_SIGNALS = 5
};

int num = 0;

void
handler(int signum)
{
    if (num < MAX_SIGNALS) {
        printf("%d\n", num++);
        fflush(stdout);
    } else {
        exit(0);
    }
}

int main()
{
    sigaction(SIGHUP, &(struct sigaction)
            { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
    int cur_pid = getpid();
    printf("%d\n", cur_pid);
    fflush(stdout);
    while(1) {
        pause();
    }
    signal(SIGHUP, SIG_DFL);
    exit(0);
}
