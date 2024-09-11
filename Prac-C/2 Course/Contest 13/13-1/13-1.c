#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

enum
{
    BASE_YEAR = 1900,
    BASE_MON = 1
};

int
main(void)
{

    int fd[2];
    time_t timer;
    struct tm *cur_time;

    if (pipe(fd) == -1) {
        _exit(1);
    }
    int pid = fork();
    if (pid < 0) {
        _exit(1);
    } else if (pid == 0) {
        int pid2 = fork();
        if (pid2 < 0) {
            _exit(1);
        } else if(pid2 == 0) {
            int pid3 = fork();
            if (pid3 < 0) {
                _exit(1);
            } else if (pid3 == 0) {
                timer = time(NULL);
                cur_time = localtime(&timer);
                int day = cur_time->tm_mday;
                int month = cur_time->tm_mon + BASE_MON;
                int year = cur_time->tm_year + BASE_YEAR;
                write(fd[1], &day, sizeof(day));
                write(fd[1], &month, sizeof(month));
                write(fd[1], &year, sizeof(year));
                close(fd[1]);
                _exit(0);
            } else {
                waitpid(pid3, NULL, 0);
                int day;
                read(fd[0], &day, sizeof(day));
                printf("D:%02d\n", day);
                fflush(stdout);
                wait(NULL);
                _exit(0);
            }
        } else {
            waitpid(pid2, NULL, 0);
            int mon;
            read(fd[0], &mon, sizeof(mon));
            printf("M:%02d\n", mon);
            fflush(stdout);
            wait(NULL);
            _exit(0);
        }
    } else {
        waitpid(pid, NULL, 0);
        int year;
        read(fd[0], &year, sizeof(year));
        printf("Y:%d\n", year);
        fflush(stdout);
        _exit(0);
    }
}
