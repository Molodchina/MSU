#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>


enum
{
    CHMOD = 0755,
    FORM_STR_LEN = 2,
    MAX_PATH = 20
};


int main(int argc, char *argv[])
{
    const char header_1[] = "#!/usr/bin/python3\nimport sys\n";
    const char header_2[] = "from sys import argv\nfrom os import remove\n";
    const char ch_str_dig[] = "sys.set_int_max_str_digits(500000)\n";
    const char out[] = "print(";
    const char input[] = "%s * ";
    const char rm[] = "1)\nremove(argv[0])\n";

    if (argc < 1) {
        return 0;
    }

    char path[MAX_PATH];
    struct timeval cur_time;
    gettimeofday(&cur_time, NULL);
    snprintf(path, MAX_PATH, "/tmp/script%ld.py", cur_time.tv_usec);
    int fd = creat(path, CHMOD);
    if (fd < 0) {
        fprintf(stderr, "script create err\n");
        exit(1);
    }
    errno = 0;
    FILE *script = fdopen(fd, "w");
    if (errno) {
        fprintf(stderr, "script open err\n");
        exit(1);
    }
    if (fprintf(script, header_1) < strlen(header_1)) {
        fprintf(stderr, "header 1 write err\n");
        exit(1);
    }
    if (fprintf(script, header_2) < strlen(header_2)) {
        fprintf(stderr, "header 2 write err\n");
        exit(1);
    }

    if (fprintf(script, ch_str_dig) < strlen(ch_str_dig)) {
        fprintf(stderr, "max str digits change err\n");
        exit(1);
    }

    if (fprintf(script, out) < strlen(out)) {
        fprintf(stderr, "output write err\n");
        exit(1);
    }

    for (int i = 1; i < argc; ++i) {
        if (fprintf(script, input, argv[i])
            <= strlen(input) - FORM_STR_LEN) {
            fprintf(stderr, "input write err\n");
            exit(1);
        }
    }
    if (fprintf(script, rm) < strlen(rm)) {
        fprintf(stderr, "file remove write err\n");
        exit(1);
    }
    fclose(script);
    if (execlp(path, path, NULL) < 0) {
        fprintf(stderr, "script exec err\n");
        exit(1);
    }
    return 0;
}