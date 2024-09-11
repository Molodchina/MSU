#include <stdio.h>
#include <errno.h>
#include <stdlib.h>



enum
{
    DEC_BASE = 10,
    HEX_BASE = 16,
    FORMAT_LEN = 5,
    ADDR_LEN = 9,
};


unsigned long
getvalul(char *str)
{
    char *eptr = NULL;
    errno = 0;
    unsigned long long tmp = strtoull(str, &eptr, DEC_BASE);
    if (errno || *eptr || eptr == str
        || (unsigned long) tmp != tmp) {
        exit(EXIT_FAILURE);
    }
    return ((unsigned long) tmp);
}

unsigned int
getvalh(char *str)
{
    char *eptr = NULL;
    errno = 0;
    unsigned long tmp = strtoul(str, &eptr, HEX_BASE);
    if (errno || *eptr || eptr == str
        || (unsigned int) tmp != tmp) {
        exit(EXIT_FAILURE);
    }
    return ((unsigned int) tmp);
}

int main(int argc, char *argv[])
{
    if (argc < 4) {
        fprintf(stderr, "Arguments err\n");
        exit(EXIT_FAILURE);
    }

    unsigned long cache_size = getvalul(argv[2]);
    unsigned long block_size = getvalul(argv[3]);

    unsigned int block_count = cache_size / block_size;
    unsigned int *cache = calloc(block_count, sizeof(*cache));
    unsigned int *flags = calloc(block_count, sizeof(*flags));

    char format[FORMAT_LEN] = {};
    unsigned int adr;
    long size, val, count = 0;
    while (scanf("%s %x %ld %ld\n", format, &adr, &size, &val) > 0) {
        if (format[0] != 'R') {
            continue;
        }
        adr /= block_size;

        unsigned int cache_block_num = adr % block_count;
        if (cache[cache_block_num] != adr && flags[cache_block_num]) {
            ++count;
        } else {
            flags[cache_block_num] = 1;
        }
        cache[cache_block_num] = adr;
    }

    printf("%ld\n", count);

    free(cache);
    free(flags);
    return 0;
}