#include <stdio.h>

int sec_to_dec(char s[4], int size){
    int n=1, an=0, temp;
    for(int i=size-1; i>=0; i--){
        temp=s[i]-'0';
        an+=n*temp;
        n*=16;
    }
    return an;
}

int dv_to_dec(char s[16]){
    int n=1, an=0, temp, size=16;
    for(int i=size-1; i>=0; i--){
        if(s[i]-'0'>9) temp=s[i]-'a'+10;
        else temp=s[i]-'0';
        an+=n*temp;
        n*=2;
    }
    return an;
}

int main(void){
    char s1[4]="28d4";
    char s2[4]="2852";
    char s3[4]="5d8c";
    char s4[4]="6ff7";
    int res1=sec_to_dec(s1,4);
    int res2=sec_to_dec(s2,4);
    int res3=sec_to_dec(s3,4);
    int res4=sec_to_dec(s4,4);
    char X[16]="0111110111111100";
    char Y[16]="0110111?1100011?";
    char Z[16]="?010101011010111";
    int x=dv_to_dec(X);
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            for(int f=0; f<2; f++){
                Y[7]=i;
                Y[15]=j;
                Z[0]=f;
                int y=dv_to_dec(Y);
                int z=dv_to_dec(Z);
                if((z & x)==res1) printf("1\n");
                if((x ^ (z << 1))==res2) printf("2\n");
                if((x & (y << 1))==res3) printf("3\n");
                if((y | (z >> 2))==res4) printf("4\n");
                printf("---------\n");
            }
        }
    }
    return 0;
}
