#include <stdio.h>
#include <math.h>

int m[3400], i_m=1, temp;

int if_simp(int a){
    int flag=1, sqr=sqrt((double)a);
    for(int i=0; flag && i<i_m && m[i]<=sqr; i++){
        if(a%m[i]==0) flag=0;
    }
    return flag;
}

void rec(int a, int b){
    if(b==temp){
        printf("%d ", a);
        return;
    }
    if(if_simp(a*10+1)) rec(a*10+1, b+1);
    if(if_simp(a*10+3)) rec(a*10+3, b+1);
    if(if_simp(a*10+7)) rec(a*10+7, b+1);
    if(if_simp(a*10+9)) rec(a*10+9, b+1);
}

int main(void){
    int a=31623, i=3, sqr, flag;
    m[0]=2;
    while(i<a){
        flag=1;
        sqr=sqrt((double)i);
        for(int j=0; (flag)&&(j<i_m)&&(m[j]<=sqr); j++)
            if(i%m[j]==0) flag=0;
        if(flag) m[i_m++]=i;
        i++;
    }
    scanf("%d", &temp);
    rec(2, 1);
    rec(3, 1);
    rec(5, 1);
    rec(7, 1);
    return 0;
}

