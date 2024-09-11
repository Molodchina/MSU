#include <stdio.h>

int main(void)
{
    int s=0, n=1;
    while (s+n*(3*n-1)<=2025*(n+1)){
        s+=n*(3*n-1);
        n++;
    }
    printf("%d", n-1);
    return 0;
}
