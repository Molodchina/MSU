#include <stdio.h>

int change_str(char s[20]){
    int amount=0;
    for (int i=18; i>0; i--){
        if (s[i]=='1'){
            amount++;
        }
        else if(s[i]=='2'){
            amount++;
            if (i >= 1) s[i-1] += 1;
            else amount++;
        }
        else if(s[i]=='3'){
            if (i >= 1) s[i-1] += 1;
            else amount++;
        }
    }
    printf("%d", amount);
    return 0;
}

int into_tr(unsigned long x){
    char s[20];
    int i=0;
    for (int j=0; j<19; j++) s[j]='0';
    while (x>0){
        if (x%3==0) s[18-i]='0';
        else if (x%3==1) s[18-i]='1';
        else s[18-i]='2';
        x/=3;
        i++;
    }
    return change_str(s);
}



int main(void)
{
    int n;
    scanf("%d", &n);
    into_tr(n);
    return 0;
}
