#include <stdio.h>

int main(void){
    double s = 10000000;
    double p = 0.09;
    for(int i = 1; i < 20; i++){
        s+=s*p;
        printf("%d: %f\n", i, s);
    }
    return 0;
}
