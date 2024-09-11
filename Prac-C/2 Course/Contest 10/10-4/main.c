#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <sys/mman.h>
#include <dlfcn.h>


enum
{
    ARG_POS = 3,
    DYN_FUNC_POS = 2,
    DYN_LIB_POS = 1
};


struct Args
{
    char buf[64];
};

int
main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Arguments amount err\n");
        exit(1);
    }

    void *dyn_lyb = dlopen(argv[DYN_FUNC_POS], RTLD_LAZY);
    char *err = dlerror();
    if (err == NULL) {
        fprintf(stderr, "dynamic lib open err\n");
        exit(1);
    }

    void *func = dlsym(dyn_lyb, argv[DYN_FUNC_POS]);
    err = dlerror();
    if (err != NULL) {
        fprintf(stderr, "dynamic lib func err\n");
        exit(1);
    }

    struct Args arg = {};
    ssize_t len = 0;

    char fun_type = argv[ARG_POS][0];

    ssize_t i = 1;
    while (argv[ARG_POS][i] != '\0') {
        if (argv[ARG_POS][i] == 'i') {
            char *eptr = NULL;
            errno = 0;
            long tmp = strtol(argv[3 + i], &eptr, 10);
            if (errno || *eptr || eptr == argv[ARG_POS + i] || (int) tmp != tmp) {
                fprintf(stderr, "func (int) arg err\n");
                exit(1);
            }
            int val = (int) tmp;

            int tmp_offset = 0;
            while (tmp_offset < sizeof(tmp_offset)) {
                //printf("%c\n", (char) (val>>(tmp_offset * 8)));
                arg.buf[len++] = (char) (val>>(tmp_offset * 8));
                ++tmp_offset;
            }
            //printf("1-----\n");
        } else if (argv[ARG_POS][i] == 'd') {
            char *eptr = NULL;
            errno = 0;
            double tmp = strtod(argv[ARG_POS + i], &eptr);
            if (errno || *eptr || eptr == argv[ARG_POS + i]) {
                fprintf(stderr, "func (double) arg err\n");
                exit(1);
            }
            char *tmp_val = (char *) &tmp;

            int tmp_len = 0;
            while (tmp_len < sizeof(tmp)) {
                //printf("%c\n", *(tmp_val + tmp_len));
                arg.buf[len++] = *(tmp_val + tmp_len++);
            }
            //printf("2-----\n");
        } else if (argv[ARG_POS][i] == 's'){
            char *tmp_val = &argv[ARG_POS + i];
            int tmp_len = 0;
            while (tmp_len < sizeof(tmp_val)) {
                //printf("%c\n", *(argv[3 + i] + tmp_len++));
                arg.buf[len++] = *(tmp_val + tmp_len++);
            }
            //printf("3-----\n");
        } else {
            fprintf(stderr, "func arg (nor i|d|s) err\n");
            exit(1);
        }
        ++i;
    }
    //printf("-----\n");

    if (fun_type == 'i') {
        printf("%d\n", ((__attribute__((stdcall)) int (*)(struct Args)) func)(arg));
    } else if (fun_type == 'd') {
        printf("%.10g\n", ((__attribute__((stdcall)) double (*)(struct Args)) func)(arg));
    } else if (fun_type == 's') {
        printf("%s\n", ((__attribute__((stdcall)) char * (*)(struct Args)) func)(arg));
    } else {
        ((__attribute__((stdcall))  void (*)(struct Args)) func)(arg);
    }
    //printf("-----\n");

    if (dlclose(dyn_lyb) != 0 || dlerror()) {
        fprintf(stderr, "dynamic lib close err\n");
        exit(1);
    }

    return(0);
}