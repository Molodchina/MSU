#include <stdio.h>

int main(void)
{
    int n, max1, max2, max3, current;
    scanf("%d", &n);
    for (int i=0; i<3; i++){
        scanf("%d", &current);
        if (i==0) max1=current;
        if (i==1){
            if (current>=max1){
                max2=max1;
                max1=current;
            }
            else max2=current;
        }
        if (i==2){
            if (current>=max1){
                max3=max2;
                max2=max1;
                max1=current;
            }
            else if(current>=max2){
                max3=max2;
                max2=current;
            }
            else max3=current;
        }
    }
    for (int i=0; i<n-3; i++){
        scanf("%d", &current);
        if (current>=max1){
                max3=max2;
                max2=max1;
                max1=current;
            }
        else if(current>=max2){
            max3=max2;
            max2=current;
        }
        else if(current>max3) max3=current;
    }
    printf("%d %d %d", max1, max2, max3);
    return 0;
}
