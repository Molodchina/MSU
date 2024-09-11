#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <inttypes.h>

enum
{
    S_SIZE = 9,
    FRST_BIT = 1,
    SCND_BIT = 1<<1,
    THRD_BIT = 1<<2
};

int
main(int argc, char*argv[])
{
    for (int i = 1; i < argc; ++i) {
        char *eptr = NULL;
        errno = 0;
        long tmp = strtol(argv[i], &eptr, 10);
        if (errno || *eptr || eptr == argv[i]
            || (int32_t) tmp != tmp) {
            return 1;
        }
        const char answ[] = "rwxrwxrwx";
        int j = 0;

        while (tmp > 0) {
            for (int i = 1; i <= 4; i <<= 1) {

            }
            tmp /= 10;
        }

        printf("%s\n", answ);

    }
    return 0;
}