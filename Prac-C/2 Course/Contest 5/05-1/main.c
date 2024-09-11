#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

enum { MAX_SIZE = 1<<10 };

int
main(int argc, char *argv[])
{
    unsigned long long amount = 0;
    for (int i = 1; i < argc; ++i) {
        struct stat stb;
        if (lstat(argv[i], &stb) >= 0 && S_ISREG(stb.st_mode)
            && stb.st_size % MAX_SIZE == 0 && stb.st_nlink == 1 && S_ISLNK(stb.st_mode) == 0) {
            amount += stb.st_size;
        }
    }
    printf("%llu\n", amount);
    return 0;
}