#include <stdio.h>

int m[20];

int bin_find(int x, int amount){
    int max=19, f=1, cur_amount=0, a, temp=0;
    for (int i=0; i<20; i++){
        m[i]=f;
        f*=3;
    }
    for (int i=0; i<19; i++){
        if (m[i]>x){
            max=i;
            break;
        }
        else if (m[i]==x) return 1;
    }
    printf("Amount: %d; max: %d\n", amount, m[max]);
    while ((x>0)||(f<=max)){
        if (x==m[max-f]){
            printf("1.1:\n");
            printf("X==M[L}");
            return amount+1;
        }
        else if (x>m[max-f]){
            printf("1.2:\n");
            x-=m[max-f];
            a = bin_find(x, amount+1);
            if (a!=0) return a;
        }
        f++;
    }
    if (temp=0){
        x=m[max]-x;
        a = bin_find(x, amount+1);
        if (a!=0) return a;
        else return 0;
    }
}


int main(void)
{
    int mas[20], n, answer, f=1, amount=0;
    for (int i=0; i<19; i++){
        mas[i]=f;
        f*=3;
    }
    scanf("%d", &n);
    answer = bin_find(n, amount);
    if (answer==0) printf("-1");
    else printf("%u", answer);
    return 0;
}
