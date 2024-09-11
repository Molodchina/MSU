#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <sys/mman.h>



enum
{
    CHMOD = 0777
};


int
main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "Arguments amount err\n");
        exit(1);
    }

    char *eptr = NULL;
    errno = 0;
    long tmp = strtol(argv[2], &eptr, 10);
    if (errno || eptr == argv[2] || (int) tmp != tmp) {
        fprintf(stderr, "rows value err\n");
        exit(1);
    }
    int rows = (int) tmp;

    eptr = NULL;
    errno = 0;
    tmp = strtol(argv[3], &eptr, 10);
    if (errno || eptr == argv[3] || (int) tmp != tmp) {
        fprintf(stderr, "rows value err\n");
        exit(1);
    }
    int cols = (int) tmp;

    int fdl = open(argv[1], O_RDWR | O_TRUNC | O_CREAT, (mode_t) CHMOD);
    if (fdl == -1) {
        fprintf(stderr, "file open err\n");
        exit(1);
    }

    unsigned long *buf = NULL;
    if (ftruncate(fdl, (off_t) (rows * cols * sizeof(*buf))) != 0) {
        fprintf(stderr, "file err\n");
        exit(1);
    }

    buf = mmap(NULL, (size_t) rows * cols * sizeof(*buf), PROT_WRITE | PROT_READ, MAP_SHARED, fdl, (off_t) 0);
    if (buf == MAP_FAILED) {
        fprintf(stderr, "mapping err\n");
        exit(1);
    }
    close(fdl);

    unsigned long tmp_val = 1;
    int depth = 0;
    int tmp_row = 0;
    int tmp_col = 0;

    while (depth == 0) {
        while (tmp_col < cols - 1 - depth) {
            buf[cols * tmp_row + tmp_col++] = tmp_val++;
            if (tmp_val >= rows * cols) {
                break;
            }
        }
        while (tmp_row < rows - 1 - depth) {
            buf[cols * (tmp_row++) + tmp_col] = tmp_val++;
            if (tmp_val >= rows * cols) {
                break;
            }
        }
        while (tmp_col > depth) {
            buf[cols * tmp_row + tmp_col--] = tmp_val++;
            if (tmp_val >= rows * cols) {
                break;
            }
        }
        while (tmp_row > depth) {
            buf[cols * (tmp_row--) + tmp_col] = tmp_val++;
            if (tmp_val >= rows * cols) {
                break;
            }
        }
        ++depth;
    }

    tmp_col = 1;
    tmp_row = 1;
    while (tmp_val < rows * cols) {
        while (buf[cols * tmp_row + tmp_col + 1] == 0) {
            buf[cols * tmp_row + tmp_col++] = tmp_val++;
            if (tmp_val >= rows * cols) {
                break;
            }
        }
        while (buf[cols * (tmp_row + 1) + tmp_col] == 0) {
            buf[cols * (tmp_row++) + tmp_col] = tmp_val++;
            if (tmp_val >= rows * cols) {
                break;
            }
        }
        while (buf[cols * tmp_row + tmp_col - 1] == 0) {
            buf[cols * tmp_row + tmp_col--] = tmp_val++;
            if (tmp_val >= rows * cols) {
                break;
            }
        }
        while (buf[cols * (tmp_row - 1) + tmp_col] == 0) {
            buf[cols * (tmp_row--) + tmp_col] = tmp_val++;
            if (tmp_val >= rows * cols) {
                break;
            }
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (buf[cols * i + j] == 0) {
                buf[cols * i + j] = tmp_val++;
            }
        }
    }

    if (munmap(buf, (size_t) rows * cols * sizeof(*buf)) != 0) {
        fprintf(stderr, "mem clearance err\n");
        exit(1);
    }

    return(0);
}