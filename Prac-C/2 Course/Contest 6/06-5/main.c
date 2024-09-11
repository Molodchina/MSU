#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>



ssize_t
getcwd2(int fd, char *buf, size_t size)
{
    if (fd < 0) {
        fprintf(stderr, "dir err\n");
        exit(1);
    }

    int fd_end = open("./", O_RDONLY);
    if (fd_end < 0) {
        fprintf(stderr, "open file err\n");
        exit(1);
    }

    if (fchdir(fd) == -1) {
        fchdir(fd_end);
        return -1;
    }

    struct stat stb_root, stb_prev, stb_cur;
    char path[PATH_MAX] = {};
    ssize_t len = 0;

    if (stat("/", &stb_root) < 0 || stat("./", &stb_prev) < 0) {
        fchdir(fd_end);
        return -1;
    }

    while (stb_root.st_ino != stb_prev.st_ino
            || stb_root.st_dev != stb_prev.st_dev) {
        DIR *dp_cur = opendir("./../");
        if (dp_cur == NULL) {
            fchdir(fd_end);
            return -1;
        }

        struct dirent *pDir;
        char tmp[PATH_MAX] = {};
        char fl = 0;

        while ((pDir = readdir(dp_cur)) != NULL) {
            strcpy(tmp, "./../");
            strcat(tmp, pDir->d_name);

            if (lstat(tmp, &stb_cur) != 0 || !S_ISDIR(stb_cur.st_mode)
                    || strcmp(pDir->d_name, ".") == 0
                        || strcmp(pDir->d_name, "..") == 0) {
                continue;
            }

            if (stb_cur.st_ino == stb_prev.st_ino
                    && stb_cur.st_dev == stb_prev.st_dev) {
                fl = 1;
                char tmp_respath[PATH_MAX] = {};
                strcpy(tmp_respath, "/");
                strcat(tmp_respath, pDir->d_name);
                strcat(tmp_respath, path);
                strcpy(path, tmp_respath);
                len = (ssize_t) strlen(path);
                break;
            }
        }

        if (fl == 0) {
            fchdir(fd_end);
            return -1;
        }
        if (chdir("./../") != 0 || stat("./", &stb_prev)) {
            fchdir(fd_end);
            return -1;
        }
        closedir(dp_cur);
    }

    fchdir(fd_end);
    if (len == 0){
        path[len++] = '/';
    }
    if (size > 0) {
        strncpy(buf, path, size - 1);
        buf[size - 1] = '\0';
    }
    return len;
}
