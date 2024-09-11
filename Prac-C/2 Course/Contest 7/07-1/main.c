#include <stdio.h>



int
main(void)
{
    char c;
    static char str[] = "18446744073709551616";
    signed long long val = 0;
    char changed_fl = 0;
    while ((c = getchar())) {
        if (c == EOF) {
            if (changed_fl == 1) {
                printf("%lld\n", val);
            }
            changed_fl = 0;
            val = 0;
            break;
        }
        if (c == '\n' || c == ' ') {
            if (changed_fl == 1) {
                printf("%lld\n", val);
            }
            changed_fl = 0;
            val = 0;
            continue;
        }
        if (changed_fl == -1) {
            continue;
        }
        if (c == 'a' || c == '1' || c == '0') {
            signed long long tmp = val;
            switch (c) {
                case 'a':
                    changed_fl = 1;
                    if (__builtin_saddll_overflow(tmp, (signed long long) -1, &tmp)) {
                        puts(str);
                        val = 0;
                        changed_fl = -1;
                        continue;
                    }
                    break;
                case '1':
                    changed_fl = 1;
                    if (__builtin_saddll_overflow(tmp, (signed long long) 1, &tmp)) {
                        puts(str);
                        val = 0;
                        changed_fl = -1;
                        continue;
                    }
                    break;
                default:
                    changed_fl = 1;
                    break;
            }
            if (__builtin_smulll_overflow(val, (signed long long) 2, &val)){
                puts(str);
                val = 0;
                changed_fl = -1;
                continue;
            }
            if (__builtin_saddll_overflow(val, tmp, &val)) {
                puts(str);
                val = 0;
                changed_fl = -1;
                continue;
            }
        } else {
            continue;
        }
    }
    return 0;
}