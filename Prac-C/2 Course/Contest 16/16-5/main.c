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
#include <errno.h>



enum
{
    DEC_BASE = 10
};

long
getvall(char *str)
{
    char *eptr = NULL;
    errno = 0;
    long long tmp = strtoll(str, &eptr, DEC_BASE);
    if (errno || *eptr || eptr == str
            || (long) tmp != tmp) {
        exit(EXIT_FAILURE);
    }
    return ((long) tmp);
}

double
getvald(char *str)
{
    char *eptr = NULL;
    errno = 0;
    double tmp = strtod(str, &eptr);
    if (errno || *eptr || eptr == str) {
            exit(EXIT_SUCCESS);
    }
    return tmp;
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Arguments err\n");
        exit(EXIT_FAILURE);
    }

    double left = getvald(argv[1]);
    double right = getvald(argv[2]);
    long val = getvall(argv[3]);


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