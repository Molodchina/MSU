#include <stdio.h>
int dv_to_dec(char x[33]){
    int f=0, j=1;
    for (int i=31; i>=0; i--){
        if (x[i]=='1'){
            f+=j;
        }
        j*=2;
    }
    return f;
}

int shift_r_k(char s[33], int k){
    char x[33];
    for (int j=0; j<32; j++){
        x[j]='0';
    }
    for(int i=0; i<32; i++){
        if (i<(32-k)){
            x[i+k]=s[i];
        }
        else{
            x[i+k-32]=s[i];
        }
    }
    return dv_to_dec(x);
}

int half_bit(unsigned long x, int k){
    char s[33]={};
    int i=0;
    for (int j=0; j<32; j++){
        s[j]='0';
    }
    while (x>0){
        if (x%2==0) s[31-i]='0';
        else s[31-i]='1';
        x=x/2;
        i++;
    }
    return shift_r_k(s, k);
}



int main(void)
{
    int n, k, answer;
    scanf("%d %d", &n, &k);

    answer = half_bit(n, k);
    printf("%u", answer);
    return 0;
}
