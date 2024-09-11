#include <stdio.h>
#include <string.h>



void
refrag(char *buf, long long place, int rep)
{
    for (long long i = place; buf[i + rep - 1] != '\0'; ++i) {
        buf[i] = buf[i + rep];
    }
}

void
normalize_path(char *buf)
{
    if (buf == NULL) {
        return;
    }
    long long len = 0;
    char prev1, prev2, cur;
    while (buf[len] != '\0') {
        if (len > 2) {
            prev2 = buf[len - 2];
            prev1 = buf[len - 1];
            cur = buf[len];
            if (prev2 == '/' && prev1 == '.' && cur == '/') {
                refrag(buf, len - 1, 2);
                len -= 3;
            }
        }
        ++len;
    }
    while (len >= 3) {
        if (buf[3] == '/' && buf[1] == '.' && buf[2] == '.') {
            refrag(buf, 1, 3);
            len -= 3;
        } else {
            break;
        }
    }
    printf("%s\n", buf);
    for (long long i = 0; i < len; ++i) {
        if (i >= 6 && buf[i - 3] == '/' && buf[i-2] == '.'
                && buf[i - 1] == '.' && buf[i] == '/' && !(buf[i-4] == '.'
                    && buf[i-5] == '.' && buf[i-6] == '/')) {
            long long j;
            for (j = 0; i - j - 4 >= 0; ++j) {
                if (buf[i - j - 4] == '/') {
                    break;
                }
            }
            if (i - j - 4 == 0) {
                --j;
                refrag(buf, i - j - 4, 4 + j + 1);
                i -= 4 + j + 1;
                len -= 4 + j + 1;
            } else {
                refrag(buf, i - j - 4, 4 + j);
                i -= 4 + j;
                len -= 4 + j;
            }
        }
        if (i == len - 1 && i >= 3 && buf[i - 2] == '/' && buf[i - 1] == '.'
                && buf[i] == '.' && !(buf[i - 3] == '.'
                    && buf[i - 4] == '.' && buf[i - 5] == '/')) {
            long long j;
            for (j = 0; i - j - 3 >= 0; ++j) {
                if (buf[i - j - 3] == '/') {
                    break;
                }
            }
            if (i - j - 3 == 0) {
                --j;
                refrag(buf, i - j - 3, 3 + j + 1);
                i -= 3 + j + 1;
                len -= 3 + j + 1;
            } else {
                refrag(buf, i - j - 3, 3 + j);
                i -= 3 + j;
                len -= 3 + j;
            }
        }
    }
    while (len >= 3) {
        if (buf[3] == '/' && buf[1] == '.' && buf[2] == '.') {
            refrag(buf, 1, 3);
            len -= 3;
        } else {
            break;
        }
    }
    if (len >= 2 && buf[len - 1] == '.' && buf[strlen(buf) - 2] == '/'){
        buf[len - 1] = '\0';
        --len;
    }
    if (len >= 3 && buf[len - 1] == '.' && buf[strlen(buf) - 3] == '/' && buf[strlen(buf) - 2] == '.'){
        buf[len - 2] = '\0';
        len -= 2;
    }
    if (buf[strlen(buf) - 1] == '/' && strlen(buf) > 1){
        buf[len- 1] = '\0';
        len -= 1;
    }
    if (buf[0] == '/' && buf[1] == '/'){
        refrag(buf, 1, 1);
        --len;
    }
    if (len > 1 && buf [len - 1] == '/') {
        buf[len - 1] = '\0';
        --len;
    }
}

int
main(void)
{
    char buf[] = "/a/b/../../..";
    normalize_path(buf);
    printf("%s\n", buf);
    return 0;
}
