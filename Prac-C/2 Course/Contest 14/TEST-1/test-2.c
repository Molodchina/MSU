#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

void handler(int s)
{
    static const char msg[] = "signal received\n";
    int e = errno;
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    errno = e;
}

int main()
{
    int a, b;
    sigaction(SIGINT, &(struct sigaction) { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
    while (scanf("%d%d", &a, &b) == 2) {
        printf("%d\n", a + b);
    }
}