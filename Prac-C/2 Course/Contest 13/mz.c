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
    time_t sec_time;
    struct tm *st_time;
    int fd[2], i, pid = 0;
    if (pipe(fd) == -1) {
        _exit(1);
    }
    pid = fork();
    if (pid == -1) {
        _exit(1);
    } else if (pid == 0) {
        int pid2 = fork();
        if (pid2 == -1) {
            _exit(1);
        } else if (pid2 == 0) {
            int pid3 = fork();
            if (pid3 == -1) {
                _exit(1);
            } else if (pid3 == 0) {
                sec_time = time(NULL);
                for (i = 0; i < 3; ++i) {//записали в файл
                    write(fd[1], &sec_time, sizeof(sec_time));
                }
                close(fd[1]);
                return 0;
            } else { //внук
                waitpid(pid3, NULL, 0);
                read(fd[0], &sec_time, sizeof(sec_time));
                st_time = localtime(&sec_time);
                printf("D:%d\n", st_time->tm_mday);
                fflush(stdout);
                return 0;
            }
        } else { //сын
            waitpid(pid2, NULL, 0);
            read(fd[0], &sec_time, sizeof(sec_time));
            st_time = localtime(&sec_time);
            printf("M:%d\n", st_time->tm_mon + BASE_MON);
            fflush(stdout);
            return 0;
        }
    } else { //отец
        waitpid(pid, NULL, 0);
        read(fd[0], &sec_time, sizeof(sec_time));
        st_time = localtime(&sec_time);
        printf("Y:%d\n", st_time->tm_year + BASE_YEAR);
        fflush(stdout);
        return 0;
    }
    return 0;
}