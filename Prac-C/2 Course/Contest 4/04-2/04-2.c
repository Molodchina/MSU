#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>



int
main(int argc, char *argv[]) {
    if (argc != 3) {
        exit(1);
    }

    char *eptr = NULL;
    errno = 0;
    long amount = strtol(argv[2], &eptr, 10);

    if (errno || *eptr || eptr == argv[2]) {
        fprintf(stderr, "number of elements err\n");
        exit(1);
    }

    if (amount < 2) {
        return 0;
    }

    int fdl = open(argv[1], O_RDWR);

    // open file
    if (fdl == -1) {
        fprintf(stderr, "file open err\n");
        exit(1);
    }

    double prev = 0.0;
    double tmp = 0.0;

    if (read(fdl, &prev, sizeof(prev)) != sizeof(prev)) {
        exit(0);
    }

    for (int i = 1; i < amount; ++i) {
        if (read(fdl, &tmp, sizeof(tmp)) != sizeof(tmp)) {
            exit(0);
        }
        prev = (double) tmp - prev;

        if (lseek(fdl, -(off_t)sizeof(tmp), SEEK_CUR)
                == -1) {
            exit(0);
        }
        if (write(fdl, &prev, sizeof(prev)) != sizeof(prev)) {
            fprintf(stderr, "file write err\n");
            exit(1);
        }
    }

    if (close(fdl) == -1) {
        fprintf(stderr, "file close err\n");
        exit(1);
    }
    return 0;
}