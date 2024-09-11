#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int
main(void)
{
    unsigned long long b_len;
    scanf("%llu", &b_len);

    unsigned long long *tmp = calloc(b_len - 4, sizeof(*tmp));

    for (unsigned long long i = 0; i < b_len - 4; ++i) {
        scanf("%llu", &tmp[i]);
    }

    unsigned long long n;
    while (scanf("%llu", &n) > 0) {
        unsigned long s = 0;
        unsigned long val = n;

        while (val != b_len - 1) {
            val = tmp[val - 2];
            if (val == 0 || val == b_len - 2) {
                break;
            }
            ++s;
        }
        printf("%lu\n", s);
    }
    free(tmp);

    return 0;
}
