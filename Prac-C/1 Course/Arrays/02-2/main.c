#include <stdio.h>

int main(void)
{
    int m[10001], enter=1, j=0;
    for (int i=0; i<10000; i++) m[i]=0;
    scanf("%d", &enter);
    while (enter!=0){
        m[j]=enter;
        j++;
        scanf("%d", &enter);
    }
    if (j==1) printf("%d", m[0]);
    else{
        for (int i=0; i<j; i+=2){
            printf("%d ", m[i]);
        }
        if (j%2!=0) j--;
        for (int i=j-1; i>=0; i-=2){
            printf("%d ", m[i]);
        }
    }
    return 0;
}
