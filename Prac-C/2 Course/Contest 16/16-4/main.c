#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int
main(void)
{
    unsigned n;
    unsigned val = 0;
    unsigned maxoff = 0;
    while (scanf("%u", &n) > 0) {
        unsigned long offset;
        if (n == 0) {
            continue;
        }
        offset = 1;
        while(n % (offset * 2) == 0) {
            offset *= 2;
        }
        if (val % offset == 0) {
            val += n;
        } else {
            val = (val / offset) * offset + offset;
            val += n;
        }
        if (offset > maxoff) {
            maxoff = offset;
        }
    }

    if (maxoff == 0) {
        printf("%u %u\n", 1, 1);
        exit(EXIT_SUCCESS);
    }

    if (val % maxoff != 0) {
        val = (val / maxoff) * maxoff + maxoff;
    }

    printf("%u %u\n", val, maxoff);
    exit(EXIT_SUCCESS);
}
