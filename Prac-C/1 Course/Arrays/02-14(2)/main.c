#include <stdio.h>
#include <stdlib.h>

int a[1002]={0}, ma;

void move(int x){
    int temp, end=0;
    for (int i=ma; i>=x; i--){
        temp=a[i];
        a[i]=end;
        end=temp;
    }
    ma--;
}


int main(void)
{
    int n, m[1002]={0}, temp, f[1002]={0};
    scanf("%d", &n);
    ma=n;
    for (int i=1; i<=n; i++){
        scanf("%d", &temp);
        m[i]=temp;
        if (m[i]+i>n){
            printf("-1");
            return 0;
        }
    }
    for (int i=1; i<=n; i++) a[i]=i;
    for (int i=1; i<=n; i++){
        f[i]=a[ma-m[i]];
        move(ma-m[i]);
    }
    for (int i=1; i<=n; i++) printf("%d ", f[i]);
    return 0;
}
