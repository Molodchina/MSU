#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <sys/mman.h>



enum
{
    FILE_SIZE = 65536,
    PAGE_OFFSET_MASK = 511,
    OFFSET_LEN = 9
};


int
main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Arguments amount err\n");
        exit(1);
    }

    char *eptr = NULL;
    errno = 0;
    unsigned long tabl_start = strtoul(argv[2], &eptr, 16)>>1;

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "file open err\n");
        exit(1);
    }

    unsigned short *buf = NULL;
    buf = mmap(NULL, FILE_SIZE, PROT_READ, MAP_SHARED, fd, (off_t) 0);
    if (buf == MAP_FAILED) {
        fprintf(stderr, "mapping err\n");
        close(fd);
        exit(1);
    }
    close(fd);

    unsigned short tmp_adr;
    while(scanf("%hx", &tmp_adr) == 1) {
        unsigned long temp_offset = tmp_adr&PAGE_OFFSET_MASK;
        unsigned long temp_page = tmp_adr>>OFFSET_LEN;
        long cur_adr = buf[tabl_start + temp_page];
        printf("%hu\n", buf[(cur_adr | temp_offset)>>1]);
    }

    if (munmap(buf, FILE_SIZE) != 0) {
        fprintf(stderr, "mem clearance err\n");
        exit(1);
    }

    return(0);
}