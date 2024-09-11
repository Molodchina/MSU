#include <stdio.h>

int main(void)
{
    int n, m[1500000]={0}, a[1500000]={0};
    scanf("%d", &n);
    for (int i=0; i<=n; i++){
        scanf("%d", &temp);
        if (temp)
        m[i]=temp;
    }
    for (int i=1; i<=n; i++) printf("%d ", m[i]);
    return 0;
}
