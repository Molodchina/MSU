#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>


typedef struct Node
{
    ino_t ino;
    off_t size;
    dev_t dev;
    char *name;
} Node;

int
main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "arguments err\n");
        return 1;
    }

    DIR *dpin = opendir(argv[1]);
    DIR *dpout = opendir(argv[2]);
    unsigned long long sum = 0;

    Node *dir = calloc(2, sizeof(*dir));
    size_t len = 2;

    if (dpin == NULL || dpout == NULL) {
        fprintf(stderr, "dir open err\n");
        return 1;
    }

    struct stat stb;
    struct dirent *pDir;
    char tmp[PATH_MAX] = {};
    size_t pos = 0;

    while ((pDir = readdir(dpin)) != NULL) {
        strcpy(tmp, argv[1]);
        if (argv[1][strlen(argv[1]) - 1] != '/') {
            strcat(tmp, "/");
        }
        strcat(tmp, pDir->d_name);

        if (stat(tmp, &stb) != 0 || !S_ISREG(stb.st_mode)
                || access(tmp, W_OK) == 1) {
            continue;
        }
        if (pos >= len) {
            len = len * 2 + 1;
            dir = realloc(dir, len * (sizeof(*dir)));
        }
        dir[pos].name = strdup(pDir->d_name);
        dir[pos].size = stb.st_size;
        dir[pos].dev = stb.st_dev;
        dir[pos++].ino = stb.st_ino;
    }
    while ((pDir = readdir(dpout)) != NULL) {
        strcpy(tmp, argv[1]);
        if (argv[2][strlen(argv[2]) - 1] != '/') {
            strcat(tmp, "/");
        }
        strcat(tmp, pDir->d_name);

        if (lstat(tmp, &stb) < 0) {
            continue;
        }
        for (size_t i = 0; i < pos; ++i) {
            if (strcmp(dir[i].name, pDir->d_name) == 0
                    && stb.st_ino == dir[i].ino
                        && stb.st_dev == dir[i].dev) {
                sum += dir[i].size;
                break;
            }
        }
    }
    free(dir);
    closedir(dpin);
    closedir(dpout);
    printf("%llu\n", sum);
    return 0;
}