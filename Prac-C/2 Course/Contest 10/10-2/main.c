#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct RandomGenerator
{
    void *destroy;
    void *next;
} RandomGenerator;

RandomGenerator
*random_create(int seed)
{
    RandomGenerator *rr = calloc(1, sizeof(*rr));
    rr->next = ((seed * 1103515245 + 12345) & 12345)>>2^31;
    return rr;
}

int
main(void)
{
    return 0;
}
