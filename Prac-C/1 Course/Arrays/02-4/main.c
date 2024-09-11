#include <stdio.h>

int main(void)
{
    int n, temp, amount=0;
    int a[10001]={0}, b[10001]={0};
    scanf("%d", &n);
    for (int i=0; i<n; i++){
        scanf("%d", &temp);
        a[i]=temp;
    }
    for (int i=0; i<n; i++){
        scanf("%d", &temp);
        b[i]=temp;
    }
    for (int i=0; i<n; i++){
        if (a[i]<b[i]) a[i]=b[i];
        amount+=a[i];
    }
    printf("%d", amount);
    return 0;
}
