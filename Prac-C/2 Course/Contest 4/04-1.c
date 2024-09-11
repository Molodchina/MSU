#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

enum
{
    BUF_SIZE = 4,
    BYTE = 0xFF,
    BYTE_BITS = 8
};

static const mode_t CHMOD = 0600;

int
main(int argc, char *argv[]) {
    uint32_t tmp;

    int fdl = open(argv[argc - 1],O_TRUNC |
            O_WRONLY | O_CREAT, CHMOD);

    if (fdl == -1) {
        fprintf(stderr, "file open err\n");
        exit(1);
    }

    while (scanf("%u", &tmp) == 1) {
        unsigned char buf[BUF_SIZE] = {};

        int pos = BUF_SIZE - 1;
        while (tmp > 0) {
            if (pos % 2) {
                buf[pos] = (uint8_t) (tmp & BYTE);
                tmp >>= BYTE_BITS;
            }else{
                buf[pos] = (uint8_t) (tmp & (BYTE >> 4));
                tmp >>= (BYTE_BITS / 2);
            }
            --pos;
        }

        if (write(fdl, buf, sizeof(buf)) != sizeof(buf)) {
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