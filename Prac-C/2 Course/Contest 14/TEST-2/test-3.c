#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile sig_atomic_t flag;

void handler(int s)
{
    flag = 1;
}

int main()
{
    sigaction(SIGINT, &(struct sigaction) { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
    while (1) {
        while (!flag) {
            pause();
        }
        flag = 0;
        printf("signal received\n");
    }
}