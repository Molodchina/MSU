#include <stdio.h>

void ishappy(int a[80], int n){
    int s1=0, s2=0;
    for(int i=0; i<n/2; i++) s1+=a[i];
    for(int i=n/2+1; i<n; i++) s2+=a[i];
    if (n%2!=0) n++;
    if (s1==s2) for(int i=0; i<n; i++) print("%d", a[i]);
    else if (s1>s2) nothappy1(a, n, s1-s2);
    else nothappy2(a, n);
}

void nothappy1(int a[80], int n, int d){
    while (d!=0){
        if (a[n]==9){
            a[n-1]
        }
    }
}

int main(void)
{
    int a[80]={0}, len=0;
    char c;
    c=getchar();
    while((c!=EOF)&&(c!='\n')){
        a[len]=c;
        len+=1;
        c=getchar();
    }
    printf("Len: %d\n", len);
    ishappy(a, len);
    return 0;
}
