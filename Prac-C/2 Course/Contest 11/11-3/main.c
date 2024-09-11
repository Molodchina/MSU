#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

enum
{
    LEN = 9,
    MAX_SCAN = 8,
    AMOUNT = 3
};

int
main()
{
    for (int i = 0; i < AMOUNT; ++i) {
        int pid = fork();
        if (pid == 0) {
            char s[LEN] = {};
            if (read(0, s, MAX_SCAN) < MAX_SCAN) {
                exit(1);
            }
            char *eptr = NULL;
            errno = 0;
            long long tmp = strtoll(s, &eptr, 10);
            if (errno || eptr == s || (long) tmp != tmp) {
                exit(1);
            }
            long cur = (long) tmp;
            __builtin_smull_overflow(cur, cur, &cur);
            printf("%d %ld\n", i + 1, cur);
            exit(0);
        }
    }
    for (int i = 0; i < AMOUNT; ++i) {
        wait(NULL);
    }

    return 0;
}