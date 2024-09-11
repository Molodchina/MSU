#include <stdio.h>
int bites_amount(char x[], int k){
    int f=0, j=1;
    for (int i=k-1; i>=0; i--){
        if (x[i]=='1'){
            f+=j;
        }
        j*=2;
    }
    return f;
}

int max_in_row(char s[33], int k){
    char x[k+1];
    int maxi=0, current;
    for (int j=0; j<k; j++){
        x[j]='0';
    }
    for (int j=0; j<=31-k+1; j++){
        int f = 0;
        for (int i=j; i<j+k; i++){
            x[f]=s[i];
            f++;
        }
        current = bites_amount(x, k);
        if (current>maxi) maxi=current;
    }
    return maxi;
}

int half_bit(unsigned long x, int k){
    char s[33]={};
    int i=0;
    for (int j=0; j<32; j++) s[j]='0';
    while (x>0){
        if (x%2==0) s[31-i]='0';
        else s[31-i]='1';
        x=x/2;
        i++;
    }
    return max_in_row(s, k);
}



int main(void)
{
    int n, k, answer;
    scanf("%d %d", &n, &k);
    answer = half_bit(n, k);
    printf("%u", answer);
    return 0;
}
