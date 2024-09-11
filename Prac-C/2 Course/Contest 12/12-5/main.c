#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <limits.h>


enum
{
    CHMOD = 0711,
    PATH_LEN = PATH_MAX - 12,
    EXPR_LEN = PATH_MAX - 6,
    F_STR_LEN_DIF = 1,
    BASH_F_STRS = 3,
    C_HEAD_F_STRS = 6,
    C_BODY_F_STRS = 6,
    C_FOOT_F_STRS = 9,
    F_STR_LEN = 2,
    C_BODY_VALS = 2
};


int main(int argc, char *argv[])
{
    const char bash_header[] = "#!/bin/bash\n"
                                "gcc %s -o /tmp/%s\n"
                                "/tmp/%s";
    const char c_header[] = "#include <stdio.h>\n\n"
                            "#define summon %csummon%c\n"
                            "#define disqualify %cdisqualify%c\n"
                            "#define reject %creject%c\n"
                            "int\nmain(void)\n{\n"
                            "int x;\n";
    const char c_body[] = "x = %d;\n"
                            "printf(%c%cs%c%c%c, %s);\n";
    const char c_footer[] = "remove(%c%s%c);\n"
                            "remove(%c%s%c);\n"
                            "remove(%c%s%c);\n}\n";
    //CONST FORMAT STRINGS
    const char path_form[] = "script%ld";
    const char exec_path_form[] = "/tmp/%s";
    const char c_path_form[] = "/tmp/%s.c";
    const char bash_path_form[] = "/tmp/bash%ld.sh";
    const char quote = '"';
    const char percent = '%';
    const char n_line_1 = 92;
    const char n_line_2 = 'n';
    if (argc <= 1) {
        return 0;
    }

    char path[PATH_LEN] = {};
    char c_path[PATH_MAX] = {};
    char exec_path[PATH_MAX] = {};
    char bash_path[PATH_MAX] = {};
    struct timeval cur_time;
    gettimeofday(&cur_time, NULL);

    //FORMING SCRIPT NAMES
    snprintf(path, PATH_LEN, path_form, cur_time.tv_usec);
    snprintf(c_path, PATH_MAX, c_path_form, path);
    snprintf(exec_path, PATH_MAX, exec_path_form, path);
    snprintf(bash_path, PATH_MAX, bash_path_form, cur_time.tv_usec);

    //BASH FORMING
    int bash_fd = creat(bash_path, CHMOD);
    if (bash_fd < 0) {
        fprintf(stderr, "bash create err\n");
        exit(1);
    }
    errno = 0;
    FILE *bash = fdopen(bash_fd, "w");
    if (errno) {
        fprintf(stderr, "bash open err\n");
        exit(1);
    }
    if (fprintf(bash, bash_header, c_path, path, path)
            < strlen(bash_header) - BASH_F_STRS * F_STR_LEN_DIF) {
        fprintf(stderr, "bash write err\n");
        exit(1);
    }
    fclose(bash);

    //C_FILE CREATE
    int c_fd = creat(c_path, CHMOD);
    if (c_fd < 0) {
        fprintf(stderr, "script create err\n");
        exit(1);
    }
    errno = 0;
    FILE *script = fdopen(c_fd, "w");
    if (errno) {
        fprintf(stderr, "script open err\n");
        exit(1);
    }

    //EXPRESSION FORMING
    char expr[EXPR_LEN] = {};
    size_t cur_len = strlen(argv[1]);
    if (EXPR_LEN > cur_len) {
        strncpy(expr, argv[1], EXPR_LEN - cur_len);
    } else {
        fprintf(stderr, "expression read err\n");
        exit(1);
    }
    for (int i = 2; i < argc; ++i) {
        if (EXPR_LEN > cur_len + strlen(argv[i])) {
            strncat(expr, argv[i], EXPR_LEN - cur_len);
            cur_len += strlen(argv[i]);
        } else {
            fprintf(stderr, "expression too long err\n");
            exit(1);
        }
    }

    //C FILE WRITE
    if (fprintf(script, c_header, quote, quote, quote, quote, quote,
                quote) < strlen(c_header) - C_HEAD_F_STRS * F_STR_LEN_DIF) {
        fprintf(stderr, "file header write err\n");
        exit(1);
    }

    int x;
    while(scanf("%d", &x) > 0) {
        size_t tmp_write_len = strlen(c_body) - C_BODY_F_STRS * F_STR_LEN_DIF
                - C_BODY_VALS * F_STR_LEN;
        if (fprintf(script, c_body, x, quote, percent, n_line_1,
                    n_line_2, quote, expr) < tmp_write_len) {
            fprintf(stderr, "file body write err\n");
            exit(1);
        }
    }
    if (fprintf(script, c_footer, quote, bash_path, quote, quote, c_path,
                quote, quote, exec_path, quote)
            < strlen(c_footer) - C_FOOT_F_STRS * F_STR_LEN_DIF) {
        fprintf(stderr, "file footer write err\n");
        exit(1);
    }
    fclose(script);
    //BASH EXEC
    if (execlp(bash_path, bash_path, NULL) < 0) {
        fprintf(stderr, "script exec err\n");
        exit(1);
    }
    return 0;
}