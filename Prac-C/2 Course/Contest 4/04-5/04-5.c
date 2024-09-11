#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>



int
main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "cmd arguments err\n");
        exit(1);
    }

    int fdl = open(argv[1], O_RDONLY);
    int fdl2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0600);
    if (fdl == -1 || fdl2 == -1) {
        fprintf(stderr, "file open err\n");
        exit(1);
    }

    char *eptr = NULL;
    errno = 0;
    long mod = strtol(argv[3], &eptr, 10);
    if (errno || *eptr || eptr == argv[3]
        || mod <= 0 || (int) mod != mod) {
        fprintf(stderr, "cmd MOD argument err\n");
        exit(1);
    }

    unsigned char tmp = 0;
    unsigned long long sum = 0;
    unsigned int res = 0;
    unsigned long long val = 1;
    while (read(fdl, &tmp, sizeof(tmp)) == sizeof(tmp)) {
        for (int i = 1; i <= CHAR_BIT; ++i) {
            sum = (sum + (val % mod) * (val % mod)) % mod;
            if (tmp&1) {
                res = (unsigned int) sum;
                if (write(fdl2, &res, sizeof(res)) != sizeof(res)) {
                    fprintf(stderr, "file write err\n");
                    exit(1);
                }
            }
            tmp >>= 1;
            val = (val + 1) % mod;
        }
    }

    if (close(fdl) == -1 || close(fdl2) == -1) {
        fprintf(stderr, "file close err\n");
        exit(1);
    }
    return 0;
}