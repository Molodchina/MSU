#include <stdio.h>
#include <stdlib.h>

int M(int a, int c, int d){
    while(1){
        if (a < c){
            a ^= c;
            c ^= a;
            a ^= c;
        }
        if(a > d){
            a ^= d;
            d ^= a;
            a ^= d;
        }
        else
            return a;
    }
}

int main(void){
    int a, c, d;
    scanf("%d", &a);
    scanf("%d", &c);
    scanf("%d", &d);
    a = M(a,c,d);
    printf("%d\n", a);
    return 0;
}
