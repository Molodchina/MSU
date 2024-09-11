#include <stdio.h>
#include <stdlib.h>

char* a;
char* b;
char* c;
int a_len, b_len, c_len;
int flag=0, fl=1;

int max(int a, int b, int c){
    if(a>b){
        if(a>c) return a;
        return c;
    }
    if(b>c) return b;
    return c;
}

void check(int n){
    int d;
    if(n){
        if(c_len>a_len+1){
            d=c_len-a_len;
            for(int i=c_len; i>c_len-d; i--){
                if((c[i]!='0')&&(c[i]!='?')){
                    flag=1;
                    return;
                }
            }
        }
        else if(c_len>b_len+1){
            d=c_len-b_len;
            for(int i=c_len; i>c_len-d; i--){
                if((c[i]!='0')&&(c[i]!='?')){
                    flag=1;
                    return;
                }
            }
        }
        if(a_len>c_len){
            d=a_len-c_len;
            for(int i=a_len; i>a_len-d; i--){
                if((a[i]!='0')&&(a[i]!='?')){
                    flag=1;
                    return;
                }
            }
        }
        if(b_len>c_len){
            d=b_len-c_len;
            for(int i=b_len; i>b_len-d; i--){
                if((b[i]!='0')&&(b[i]!='?')){
                    flag=1;
                    return;
                }
            }
        }
    }
}

void output(int n){
    char x;
    if(flag==1){
        printf("No");
        return;
    }
    else if(!(n+1)){
        for(int i=0; i<=a_len/2; i++){
            x=a[i];
            a[i]=a[a_len-i];
            a[a_len-i]=x;
            if((x=='?')||(a[i]=='?')){
                printf("No");
                return;
            }
        }
        for(int i=0; i<=b_len/2; i++){
            x=b[i];
            b[i]=b[b_len-i];
            b[b_len-i]=x;
            if((x=='?')||(b[i]=='?')){
                printf("No");
                return;
            }
        }
        for(int i=0; i<=c_len/2; i++){
            x=c[i];
            c[i]=c[c_len-i];
            c[c_len-i]=x;
            if((x=='?')||(c[i]=='?')){
                printf("No");
                return;
            }
        }
    }
    a[a_len+1]='\0';
    b[b_len+1]='\0';
    c[c_len+1]='\0';
    printf("%s", a);
    printf("+");
    printf("%s", b);
    printf("=");
    printf("%s\n", c);
}

/*void out(int a1){
    printf("%c %c %c\n", a[a1], b[a1], c[a1]);
    printf("%s", a);
    printf("+");
    printf("%s", b);
    printf("=");
    printf("%s\n", c);
}*/


void rev(char* m, int m_len){
    char x;
    for(int i=0; i<=m_len/2; i++){
        x=m[i];
        m[i]=m[m_len-i];
        m[m_len-i]=x;
    }
    return;
}

int if_znak(char x){
    if(x=='+') return 1;
    else if(x=='=') return 2;
    else return 0;
}

void rec(int a1, int b1){
    if(fl==0) return;
    else if(a1>a_len && a1>b_len && a1>c_len){
        if(b1==0) fl=0;
        return;
    }
    else if(a[a1]=='?' && b[a1]=='?' && c[a1]=='?'){
        a[a1]='0';
        b[a1]='0';
        if(b1==0) c[a1]='0';
        else c[a1]='1';
        rec(a1+1, 0);
        if((fl==1)&&(c_len>a1)){
            a[a1]='5';
            b[a1]='5';
            if(b1==0) c[a1]='0';
            else c[a1]='1';
            rec(a1+1, 1);
        }
    }
    else if(a[a1]=='?' && b[a1]=='?' && c[a1]!='?'){
        if(c[a1]=='9'){
            if(b1==1){
                a[a1]='4';
                b[a1]='4';
                rec(a1+1, 0);
                if((fl==1)&&(c_len>a1)){
                    a[a1]='9';
                    b[a1]='9';
                    rec(a1+1, 1);
                }
            }
            else{
                a[a1]='2';
                b[a1]='7';
                rec(a1+1, 0);
            }
        }
        else{
            if(c[a1]=='0' && b1==1){
                if(c_len>a1){
                    a[a1]='7'; b[a1]='2';
                    rec(a1+1, 1);
                }
                else{
                    flag=1;
                    return;
                }
            }
            else{
                a[a1]='0';
                if(b1==0) b[a1]=c[a1];
                else b[a1]=c[a1]-1;
                rec(a1+1, 0);
                if((fl==1)&&(c_len>a1)){
                    a[a1]='9';
                    if(b1==0) b[a1]=c[a1]+1;
                    else b[a1]=c[a1];
                    rec(a1+1, 1);
                }
            }
        }
    }
    else if(a[a1]!='?' && b[a1]=='?' && c[a1]!='?'){
        if(a[a1]>c[a1]){
            if(b1==1) b[a1]='0'+9+(c[a1]-a[a1]);
            else b[a1]='0'+10+(c[a1]-a[a1]);
            if(c_len>a1) rec(a1+1, 1);
            else{
                flag=1;
                return;
            }
        }
        else if(a[a1]<c[a1]){
            if(b1==1) b[a1]='0'+(c[a1]-a[a1])-1;
            else b[a1]='0'+(c[a1]-a[a1]);
            rec(a1+1, 0);
        }
        else{
            if(b1==0){
                b[a1]='0';
                rec(a1+1, 0);
            }
            else{
                if(c_len>a1){
                    b[a1]='9';
                    rec(a1+1, 1);
                }
                else{
                    flag=1;
                    return;
                }
            }
        }
    }
    else if(a[a1]=='?' && b[a1]!='?' && c[a1]!='?'){
        if(b[a1]>c[a1]){
            if(b1==1) a[a1]='0'+9+(c[a1]-b[a1]);
            else a[a1]='0'+10+(c[a1]-b[a1]);
            if(c_len>a1) rec(a1+1, 1);
            else{
                flag=1;
                return;
            }
        }
        else if(b[a1]<c[a1]){
            if(b1==1) a[a1]='0'+(c[a1]-b[a1])-1;
            else a[a1]='0'+(c[a1]-b[a1]);
            rec(a1+1, 0);
        }
        else{
            if(b1==0){
                a[a1]='0';
                rec(a1+1, 0);
            }
            else{
                if(c_len>a1+1){
                    a[a1]='9';
                    rec(a1+1, 1);
                }
                else{
                    flag=1;
                    return;
                }
            }
        }
    }
    else if(a[a1]!='?' && b[a1]!='?' && c[a1]!='?'){
        if(b1==1){
            if(((int)(a[a1]-'0'+b[a1]-'0')+1)%10==(int)(c[a1]-'0')){
                if((int)(a[a1]-'0'+b[a1]-'0')+1>9){
                    if(c_len>a1) rec(a1+1, 1);
                    else{
                        flag=1;
                        return;
                    }
                }
                else rec(a1+1, 0);
            }
        }
        else{
            if((int)(a[a1]-'0'+b[a1]-'0')%10==(int)(c[a1]-'0')){
                if((int)(a[a1]-'0'+b[a1]-'0')>9){
                    if(c_len>a1) rec(a1+1, 1);
                    else{
                        flag=1;
                        return;
                    }
                }
                else rec(a1+1, 0);
            }
        }
    }
    else if(a[a1]!='?' && b[a1]=='?' && c[a1]=='?'){
        if(a[a1]=='0'){
            if(b1==0){
                b[a1]='0';
                c[a1]='0';
                rec(a1+1, 0);
            }
            else{
                b[a1]='0';
                c[a1]='1';
                rec(a1+1, 0);
                if((fl==1)&&(c_len>a1)){
                    b[a1]='9';
                    c[a1]='0';
                    rec(a1+1, 1);
                }
            }
        }
        else{
            if(a[a1]=='9'){
                if(b1==1){
                    b[a1]='0';
                    c[a1]='0';
                    if(c_len>a1) rec(a1+1, 1);
                    else{
                        flag=1;
                        return;
                    }
                }
                else{
                    b[a1]='0'; c[a1]='9';
                    rec(a1+1, 0);
                    if((fl==1)&&(c_len>a1)){
                        b[a1]='1';
                        c[a1]='0';
                        rec(a1+1, 1);
                    }
                }
            }
            else{
                b[a1]='0';
                if(b1==0) c[a1]=a[a1];
                else c[a1]=a[a1]+1;
                rec(a1+1, 0);
                if((fl==1)&&(c_len>a1)){
                    b[a1]='9';
                    if(b1==0) c[a1]=a[a1]-1;
                    else c[a1]=a[a1];
                    rec(a1+1, 1);
                }
            }
        }
    }
    else if(a[a1]=='?' && b[a1]!='?' && c[a1]=='?'){
        if(b[a1]=='0'){
            if(b1==0){
                a[a1]='0';
                c[a1]='0';
                rec(a1+1, 0);
            }
            else{
                a[a1]='0';
                c[a1]='1';
                rec(a1+1, 0);
                if((fl==1)&&(c_len>a1)){
                    a[a1]='9';
                    c[a1]='0';
                    rec(a1+1, 1);
                }
            }
        }
        else{
            if(b[a1]=='9'){
                if(b1==1){
                    a[a1]='0';
                    c[a1]='0';
                    if((fl==1)&&(c_len>a1)) rec(a1+1, 1);
                    else{
                        flag=1;
                        return;
                    }
                }
                else{
                    a[a1]='0';
                    c[a1]='9';
                    rec(a1+1, 0);
                    if((fl==1)&&(c_len>a1)){
                        a[a1]='1';
                        c[a1]='0';
                        rec(a1+1, 1);
                    }
                }
            }
            else{
                a[a1]='0';
                if(b1==0) c[a1]=b[a1];
                else c[a1]=b[a1]+1;
                rec(a1+1, 0);
                if((fl==1)&&(c_len>a1)){
                    a[a1]='9';
                    if(b1==0) c[a1]=b[a1]-1;
                    else c[a1]=b[a1];
                    rec(a1+1, 1);
                }
            }
        }
    }
    else if(a[a1]!='?' && b[a1]!='?' && c[a1]=='?'){
        if((int)(a[a1]-'0'+b[a1]-'0')+b1>9){
            if((fl==1)&&(c_len>a1)){
                c[a1]='0'+((int)(a[a1]-'0'+b[a1]-'0')+b1)%10;
                rec(a1+1, 1);
            }
            else{
                flag=1;
                return;
            }
        }
        else{
            c[a1]='0'+(int)(a[a1]-'0'+b[a1]-'0')+b1;
            rec(a1+1, 0);
        }
    }
}

int main(void){
    a=malloc(sizeof(char)*200);
    b=malloc(sizeof(char)*200);
    c=malloc(sizeof(char)*200);
    char x;
    int temp=0;
    for(int i=0; i<200; i++){
        a[i]='0';
        b[i]='0';
        c[i]='0';
    }
    x=getchar();
    while(!if_znak(x)){
        if((x==EOF)&&(x=='\n')){
            printf("No");
            return 0;
        }
        a[temp]=x;
        x=getchar();
        ++temp;
    }
    a_len=temp-1;
    x=getchar();
    temp=0;
    while(!if_znak(x)){
        if((x==EOF)&&(x=='\n')){
            printf("No");
            return 0;
        }
        b[temp]=x;
        x=getchar();
        ++temp;
    }
    b_len=temp-1;
    x=getchar();
    temp=0;
    while((x!=EOF)&&(x!='\n')){
        c[temp]=x;
        x=getchar();
        ++temp;
    }
    c_len=temp-1;
    temp=max(a_len+1, b_len+1, c_len+1);

    a[temp]='\0';
    b[temp]='\0';
    c[temp]='\0';
    rev(a, a_len);
    rev(b, b_len);
    rev(c, c_len);

    check(1);
    rec(0,0);
    check(1);
    output(-1);
    return 0;
}
