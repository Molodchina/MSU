#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

enum
{
    ARG_AMOUNT = 2,
    FRST_SUF_LETTER = '.',
    SEC_SUF_LETTER = 'e',
    THRD_SUF_LETTER = 'x'
};

int
main(int argc, char *argv[])
{
    struct dirent *pDir;

    DIR *dp = NULL;
    int f_amount = 0;
    struct stat stb;
    if (argc != ARG_AMOUNT) {
        fprintf(stderr, "arguments err\n");
        exit(1);
    }

    dp = opendir(argv[1]);
    if (dp) {
        while ((pDir = readdir(dp)) != NULL) {
            char path[PATH_MAX];
            strcpy(path, argv[1]);
            strcat(path, "/");
            strcat(path, pDir->d_name);

            if (stat(path, &stb) >= 0 && S_ISREG(stb.st_mode)
                    && access(path, X_OK) == 0) {
                size_t l = strlen(pDir->d_name);
                if (l >= 4 && pDir->d_name[l-4] == FRST_SUF_LETTER && pDir->d_name[l-1] == SEC_SUF_LETTER
                        && pDir->d_name[l-2] == THRD_SUF_LETTER && pDir->d_name[l-3] == SEC_SUF_LETTER) {
                    ++f_amount;
                }
            }
        }
    } else{
        fprintf(stderr, "file path err\n");
        exit(1);
    }
    printf("%d\n", f_amount);
    closedir(dp);
    return 0;
}