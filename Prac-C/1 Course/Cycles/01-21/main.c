#include <stdio.h>


int bin_find(int m[20], int x){
    int amount=0, max=19;
    if (x==2) return 0;
    else{
        for (int i=0; i<19; i++){
            if (m[i]>x){
                max=i;
                break;
            }
            else if (m[i]==x) return 1;
        }
        int A[2]={m[max]-x, x};
        for (int j=0; j<2; j++){
            int f=1;
            x=A[j];
            if (j==0) amount=1;
            else amount=0;
            while ((x>0)&&(f<=max)){
                if (x>m[max-f]){
                    x-=m[max-f];
                    amount+=1;
                }
                else if (x==m[max-f]){
                    amount+=1;
                    x-=m[max-f];
                    return amount;
                }
                f+=1;
            }
        }
        if (x==0) return amount;
        else return 0;
    }
}


int main(void)
{
    int mas[20], n, answer, f=1;
    for (int i=0; i<19; i++){
        mas[i]=f;
        f*=3;
    }
    scanf("%d", &n);
    answer = bin_find(mas, n);
    if (answer==0) printf("-1");
    else printf("%u", answer);
    return 0;
}
