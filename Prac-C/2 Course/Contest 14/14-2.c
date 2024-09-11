#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

volatile int mode = 0;

void
handler1(int signum)
{
    mode = 0;
}

void
handler2(int signum)
{
    mode = 1;
}

int main()
{
    sigaction(SIGINT, &(struct sigaction)
            { .sa_handler = handler1, .sa_flags = SA_RESTART }, NULL);
    sigaction(SIGQUIT, &(struct sigaction)
            { .sa_handler = handler2, .sa_flags = SA_RESTART }, NULL);

    int cur_pid = getpid();
    printf("%d\n", cur_pid);
    fflush(stdout);
    int tmp;
    long long sum = 0;

    while(scanf("%d", &tmp) > 0){
        if (mode == 0) {
            sum += tmp;
            sum = (int) sum;
            printf("%lld\n", sum);
            fflush(stdout);
        } else if (mode == 1) {
            sum *= tmp;
            sum = (int) sum;
            printf("%lld\n", sum);
            fflush(stdout);
        }
    }
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    exit(0);
}