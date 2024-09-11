#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>



int
main(int argc, char *argv[])
{
    int64_t sum = 0;
    int32_t val;
    short pos = 0;
    for(int i = 1; i < argc; ++i){
        char *eptr = NULL;
        errno = 0;
        int64_t tmp = strtol(argv[i], &eptr, 10);
        if (errno || eptr == argv[i] || (int32_t) tmp != tmp) {
            continue;
        }
        if (!(*eptr) || (*eptr != 'k' && *eptr != '+' && *eptr != '-')
                || (*eptr == 'k' && eptr[1] != '+' && eptr[1] != '-')) {
            continue;
        }
        val = (int32_t) tmp;
        if (*eptr == 'k') {
            long tmp_val = (long) tmp;
            if (__builtin_smull_overflow(tmp_val, (signed long) 1000, &tmp_val)
                    || (long) tmp != val
                        || (long) tmp_val != (int32_t) tmp_val){
                continue;
            }
            val = (int32_t) tmp_val;
            pos = 1;
        }
        if (eptr[pos] == '+') {
            pos = 0;
            sum += val;
            continue;
        }
        pos = 0;
        sum -= val;
    }
    printf("%" PRId64 "\n", sum);
    return 0;
}
