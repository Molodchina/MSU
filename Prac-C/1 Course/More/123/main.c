#include <stdio.h>

int flag = 0, temp = 0;

void check(int budg, int amount, int chan){
    if((!budg)&&(!amount)&&(chan==4)){
        flag = 1;
        printf("%d", temp);
        return;
    }
    if(budg<0)
        return;
    if(amount<0)
        return;

    switch(chan){
        case 1:
            for(int i=1; i<amount-2+chan; ++i)
                check(budg-5*i, amount-i, chan+1);
            break;
        case 2:
            for(int i=1; i<amount-2+chan; ++i)
                check(budg-3*i, amount-i, chan+1);
            break;
        case 3:
            for(int i=1; i<amount-2+chan; ++i){
                temp = i;
                check(budg-i, amount-10*i, chan+1);
            }

            break;
    }
}

int main(void){
    int pers = 100;
    int budg = 100;
    check(budg,pers,1);
    return 0;
}
