#include <stdio.h>
#include <stdlib.h>

unsigned F(unsigned a){
    int c = a - 1;
    a = 1;
    while(c >= 0){
        a = 3 * a;
        --c;
    }
    return a;
}

int main(void){
    unsigned a;
    scanf("%u", &a);
    a = F(a);
    printf("%u\n", a);
    return 0;
}
