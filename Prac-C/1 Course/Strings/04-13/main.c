#include <stdio.h>

int main(void)
{
    char a[1000001];
    int flag=1, amount=0, n, f;
    char c;
    while(1){
        c=getchar();
        if ((c=='\n')||(c==EOF)) break;
        else{
            a[amount]=c;
            amount++;
        }
    }
    for(int cur=1; cur<amount; cur++){
        flag=1;
        for(int i=cur; i<amount; i++){
            n=i-cur;
            if(a[i]!=a[n]){
                flag=0;
                break;
            }
        }
        if(flag) printf("%d ", cur);
    }
    printf("%d ", amount);
    return 0;
}
