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


int chislo_8bit(char x[9]){

}


int half_bit(int a, int b, int c, int d){
    char s[33]={};
    char x[9]={};
    int f[4]={a, b, c, d};
    int i=0;
    for (int j=0; j<32; j++) s[j]='0';
    for (int j=0; j<4; j++){
        while (f[j]>0){
            if (f[j]%2==0) s[31-i]='0';
            else s[31-i]='1';
            f[j]/=2;
            i++;
        }
        x=chislo_8bit(f[j]);
    }

    return bites_amount(s);
}



int main(void)
{
    int a, b, c, d, answer;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    answer = half_bit(a, b, c, d);
    printf("%u", answer);
    return 0;
}
