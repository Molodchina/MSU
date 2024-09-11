#include <stdio.h>

int main(void)
{
    int n, m, f;
    int temp;
    int m1[100000]={0}, m2[100000]={0};
    scanf("%d", &n);
    for (int i=0; i<n; i++){
        scanf("%d", &temp);
        m1[i]=temp;
    }
    scanf("%d", &m);
    for (int i=0; i<m; i++){
        scanf("%d", &temp);
        m2[i]=temp;
    }
    if (n<m) f=m;
    else f=n;
    for (int i=0; i<f; i++){
        if (i<n) printf("%d ", m1[i]);
        if (i<m) printf("%d ", m2[i]);
    }
    return 0;
}
