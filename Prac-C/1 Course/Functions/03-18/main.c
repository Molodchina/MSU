#include <stdio.h>

int flag=1, current=0;
unsigned long h;

long long operation(unsigned long a){
    int len=1;
    while (a/len!=0){
        len*=10;
    }
    return (a+a*len);
}

int inf_seq(unsigned long x, int f){
    if (f>2010) return 0;
    x=operation(x)%2010;
    if (x==h){
        flag=0;
        return 0;
    }
    f++;
    return inf_seq(x, f);
}

int main(void)
{
    unsigned long a, n;
    scanf("%ld %ld", &a, &n);
    h=n;
    a%=2010;
    if (n>=2010){
        printf("NO");
        return 0;
    }
    else{
        if (a==n){
            printf("YES");
            return 0;
        }
        else inf_seq(a, 2);
    }
    if (flag==1) printf("NO");
    else printf("YES");
    return 0;
}
