#include <stdio.h>
#include <math.h>

int flag=0, temp=1;
int p_a=1, p_b=1;

int check1(int a, int b){
    int l=fabs(a-p_a), r=fabs(b-p_b);
    if ((p_a==a)&&(p_b==b)) flag=1;
    else if (((l!=2)||(r!=1))&&((l!=1)||(r!=2))){
        flag=1;
    }
    p_a=a;
    p_b=b;
    return 0;
}

int check2(int a, int b){
    int l=fabs(a-p_a), r=fabs(b-p_b);
    if ((p_a==a)&&(p_b==b)) flag=1;
    else if ((l!=r)&&(a!=p_a)&&(b!=p_b)){
        flag=1;
    }
    p_a=a;
    p_b=b;
    return 0;
}

int main(void)
{
    int a, b;
    char c;
    scanf ("%c", &c);
    a=c-64;
    scanf ("%d ", &b);
    while (1){
        if (temp%2==1) check1(a,b);
        else check2(a,b);
        scanf ("%c", &c);
        a=c-64;
        if ((c!='X')&&(p_a==8)&&(p_b==8)){
            flag=1;
            break;
        }
        if (c=='X') break;
        else scanf ("%d ", &b);
        temp++;
    }
    if ((flag!=0)||(p_a!=8)||(p_b!=8)) printf("Cheaters");
    else if (temp%2==0) printf("Tolik");
    else printf("Garik");
    return 0;
}
