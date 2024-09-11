#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int
main(void)
{
    char *srcpath = "~/file1.txt";
    char *dstpath = "~/file2.txt";
    struct stat stb1;
    struct stat stb2;
    if (stat(srcpath, &stb1) >= 0 && stb1.st_mode )
    return 0;
}