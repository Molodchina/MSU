#include <stdio.h>
#include <string.h>



int
parse_rwx_permissions(const char *str)
{
    const char *format_string = "rwxrwxrwx";
    int form_len = strlen(format_string);
    if (str == NULL) {
        return -1;
    }

    int res = 0;
    int val = 1<<(form_len - 1);
    for (int i = 0; i <= form_len; ++i) {
        if (str[i] == format_string[i]) {
            res += val;
        } else if (str[i] != '-') {
            return -1;
        }
        val >>= 1;
    }
    return res;
}
