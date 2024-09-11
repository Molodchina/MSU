#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

int counter = 0;

void
handler(int signum)
{
    printf("\nYou pressed ctrl+c %d TIMES, but I don't care\n", ++counter);
}

int main()
{
    int pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork err\n");
        _exit(1);
    } else if (pid == 0) {
        sigaction(SIGINT, &(struct sigaction) { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
        while(true){
            printf("Ctrl + C can't kill me!!\n");
            sleep(1000);
        }
        //Change back to the old handler
        signal(SIGINT, SIG_DFL);
        //alternatively:  signal(SIGINT, SIG_DFL);
    }
    int status;
    if (WIFSIGNALED(status) == 1 && WTERMSIG(status) > 0) {
        printf("%d\n", status);
        _exit(0);
    }
}
