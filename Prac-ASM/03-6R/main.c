#include <stdio.h>

int main(void){
    unsigned b = 0xffffffff;
    unsigned a;
    scanf("%u", &a);
    while( a != 0){
        if (a <= b)
            b = a;
        scanf("%u", &a);
    }
    printf("%u", b);
    return 0;
}
