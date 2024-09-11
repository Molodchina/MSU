#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>


enum
{
    ARG_AMOUNT = 3,
    MAX_DEPTH = 4
};

void
print_path(const char *origin_path, char *cur, size_t depth, off_t size)
{
    if (depth > MAX_DEPTH) {
        return;
    }
    char tmp_path[PATH_MAX];
    strcpy(tmp_path, origin_path);
    if (cur != NULL){
        strcat(tmp_path, "/");
        strcat(tmp_path, cur);
    }


    DIR *dp = opendir(tmp_path);
    if (dp == NULL) {
        return;
    }

    struct stat stb;
    struct dirent *pDir;
    char tmp[PATH_MAX];

    while ((pDir = readdir(dp)) != NULL) {
        strcpy(tmp, tmp_path);
        strcat(tmp, "/");
        strcat(tmp, pDir->d_name);

        if (lstat(tmp, &stb) != 0 || S_ISLNK(stb.st_mode)) {
            continue;
        }

        if (S_ISDIR(stb.st_mode)) {
            if (strcmp(pDir->d_name, ".") == 0
                || strcmp(pDir->d_name, "..") == 0) {
                continue;
            }
            if (cur == NULL) {
                print_path(origin_path, pDir->d_name, depth + 1, size);
            } else {
                char buf[PATH_MAX] = {};
                strcpy(buf, cur);
                strcat(buf, "/");
                strcat(buf, pDir->d_name);
                print_path(origin_path, buf, depth + 1, size);
            }
        }
        else if (S_ISREG(stb.st_mode) && stb.st_size <= size
                && access(tmp, R_OK) == 0) {
            if (cur == NULL) {
                printf("%s\n", pDir->d_name);
            } else {
                printf("%s/%s\n", cur, pDir->d_name);
            }
        }
    }
    closedir(dp);
}

int
main(int argc, char *argv[])
{
    if (argc != ARG_AMOUNT) {
        fprintf(stderr, "arguments err\n");
        exit(1);
    }

    char *eptr = NULL;
    errno = 0;
    long long tmp = strtoll(argv[2], &eptr, 10);
    if (errno || *eptr || eptr == argv[2]
        || (off_t) tmp != tmp) {
        fprintf(stderr, "file size err\n");
        exit(1);
    }
    off_t max_size = (int32_t) tmp;
    print_path(argv[1], NULL, 1, max_size);
    return 0;
}