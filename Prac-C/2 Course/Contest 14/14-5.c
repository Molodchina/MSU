#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

enum
{
    MAX_SIGNALS = 3
};

int num = 0;
_Atomic long long cur_prime = 0;

void
handler_int(int signum)
{
    if (num++ < MAX_SIGNALS) {
        printf("%lld\n", cur_prime);
        fflush(stdout);
    }
    if (num >= MAX_SIGNALS) {
        kill(getpid(), SIGTERM);
        exit(0);
    }
}

void
handler_term(int signum)
{
    exit(0);
}

int main()
{
    int cur_pid = getpid();
    printf("%d\n", cur_pid);
    fflush(stdout);

    sigaction(SIGINT, &(struct sigaction)
            { .sa_handler = handler_int, .sa_flags = SA_RESTART }, NULL);
    sigaction(SIGTERM, &(struct sigaction)
            { .sa_handler = handler_term, .sa_flags = SA_RESTART }, NULL);

    long long low, high;
    scanf("%lld %lld", &low, &high);
    while (low < high) {
        int flag = 0;

        if (low <= 1) {
            ++low;
            continue;
        }

        for (long long i = 2; i < low / i; ++i) {
            if (low % i == 0) {
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            cur_prime = low;
        }
        ++low;
    }

    signal(SIGINT, SIG_DFL);
    signal(SIGTERM, SIG_DFL);
    printf("%d\n", -1);
    fflush(stdout);

    exit(0);
}
