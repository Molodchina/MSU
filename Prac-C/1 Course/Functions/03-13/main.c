#include <stdio.h>


void seq(int m[15], int n, int current, int k){
    for (int i=current; i<=k; i++){
        for (int j=0; j<n; j++){
            if ((i==1)||(m[i-1]<j)){
                m[i]=j;
                if (i!=k) seq(m, n, i+1, k);
                else{
                    for (int f=1; f<=k; f++) printf("%d ", m[f]);
                    printf("\n");
                }
            }
        }
    }
}


int main(void)
{
    int n, k, m[15]={0};
    scanf("%d %d", &n, &k);
    seq(m,n,1,k);
    return 0;
}
