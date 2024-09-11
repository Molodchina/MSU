#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

short
check_endian()
{
    unsigned int x = 1;
    char *c = (char*) &x;
    return (short) *c;
}

void
swapOrder(char *buf)
{
    char tmp;
    for (size_t i = 0; i < __SIZEOF_LONG_LONG__ / 2; ++i) {
        tmp = buf[i];
        buf[i] = buf[__SIZEOF_LONG_LONG__ - i - 1];
        buf[__SIZEOF_LONG_LONG__ - i - 1] = tmp;
    }
}

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "cmd argument err\n");
        exit(1);
    }

    union
    {
        short big_end;
        short min_changed;
    } flag;
    flag.big_end = 1^check_endian();

    union {
        long long val;
        char str_val[__SIZEOF_LONG_LONG__];
    } tmp;

    int fdl = open(argv[1], O_RDWR);
    if (fdl == -1) {
        fprintf(stderr, "file open err\n");
        exit(1);
    }

    off_t min_pos = -1;
    long long min_val = 0;

    while (read(fdl, &tmp, sizeof(tmp)) == sizeof(tmp)) {
        if (flag.big_end) {
            swapOrder(tmp.str_val);
        }
        if (min_val > tmp.val || min_pos == -1) {
            min_val = tmp.val;
            min_pos = lseek(fdl, 0, SEEK_CUR) - sizeof(tmp);
        }
    }

    if (min_pos != -1 && min_val != LLONG_MIN) {
        if (min_val != LLONG_MIN) {
            tmp.val = -min_val;
        }
        if (flag.big_end){
            swapOrder(tmp.str_val);
        }
        lseek(fdl, min_pos, SEEK_SET);

        if (write(fdl, &tmp, sizeof(tmp)) != sizeof(tmp)) {
            fprintf(stderr, "file write err\n");
            exit(1);
        }
    }

    if (close(fdl) == -1) {
        fprintf(stderr, "file close err\n");
        exit(1);
    }
    return 0;
}
