#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n, m[1002]={0}, temp, a[1002]={0};
    scanf("%d", &n);
    for (int i=1; i<=n; i++){
        scanf("%d", &temp);
        m[i]=temp;
    }
    for (int i=n; i>=1; i--) a[n-i+1]=i;
    for (int i=1; i<=n; i++) printf("%d ", a[i]);
    printf("\n\n");
    for (int i=1; i<=n; i++){
        if (i+m[i]<=n){
            temp=a[i];
            a[i]=a[i+m[i]];
            a[i+m[i]]=temp;
        }
        else{
            printf("-1");
            return 0;
        }
        for (int i=1; i<=n; i++) printf("%d ", a[i]);
        printf("\n");
    }
    printf("\n");
    for (int i=1; i<=n; i++) printf("%d ", a[i]);
    return 0;
}
