#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int len, min_n='0', max_n='9', zn;
char s[2001];

int is_n(int a){
    int x=s[a];
    if((x>=min_n)&&(x<=max_n)) return 1;
    return 0;
}

int is_z(int a){
    if(s[a]=='-'){
        zn=0;
        return 1;
    }
    if(s[a]=='+'){
        zn=1;
        return 1;
    }
    if(s[a]=='*'){
        zn=2;
        return 1;
    }
    if(s[a]=='/'){
        zn=3;
        return 1;
    }
    return 0;
}

int check(int c_l, int l){
    int c_r, z, r, a, b, flag;
    while(r<len-2){
        flag=1;
        for(int j=l; j<len-2; j++){
            if(is_n(j)){
                c_l=j;
                break;
            }
            else if(j==len-3) return 0;
        }
        c_r=c_l;
        a=0;
        while(is_n(c_r+1)&&(c_r<len-1)){
            a+=s[c_r]-'0';
            a*=10;
            c_r++;
            if(c_r==len-2) return 0;
        }
        a+=s[c_r]-'0';
        char *ch1=malloc(c_r-c_l+2);
        memcpy(ch1, s+c_l, c_r-c_l+1);
        z=c_r+1;
        l=z+1;
        r=l;
        if(is_z(z)&&(is_n(l))){
            b=0;
            while(is_n(r+1)&&(r<len-1)) b+=s[r]-'0', b*=10, r++;
            b+=s[r]-'0';
            if(zn==0) a=a-b;
            else if(zn==1) a=a+b;
            else if(zn==2) a=a*b;
            else if(zn==3){
                if(b) a=a/b;
                else flag=0;
            }
            if((a<=120000)&&(a>=-120000)&&(flag)){
                char *ch2=malloc(r-l+2);
                memcpy(ch2, s+l, r-l+1);
                ch1[c_r-c_l+1]='\0';
                ch2[r-l+1]='\0';
                printf("%s %c %s", ch1, s[z], ch2);
                printf(" = %d\n", a);
            }
        }
    }
    return 1;
}

int main(void)
{
    scanf("%s", s);
    len=strlen(s);
    check(0, 0);
    return 0;
}
