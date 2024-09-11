#include <stdio.h>

int main(void)
{
    char a[10001]={0};
    int m[10001];
    int flag=1, temp=0, cur=1, amount=0, n;
    char c;
    while(1){
        c=getchar();
        if (c=='\n') break;
        else{
            a[amount]=c;
            amount++;
        }
    }
    while(cur<amount){
        flag=1;
        for(int i=0; i<amount; i++){
            n=i-cur;
            if(i<cur) n=amount-cur+i;
            if(a[i]!=a[n]){
                flag=0;
                break;
            }
        }
        if(flag==1){
            m[temp]=cur;
            temp++;
        }
        cur++;
    }
    m[temp]=amount;
    for(int i=0; i<=temp; i++) printf("%d ", m[i]);
    return 0;
}
