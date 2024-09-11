#include <stdio.h>
#include <stdlib.h>

int max(int a, int b){
    if(a>b) return a;
    else return b;
}

int if_znak(char x){
    if(x=='+') return 1;
    else if(x=='-') return 2;
    else if(x=='*') return 3;
    else return 0;
}

void output(char* result, int size_result){
    int k=0;
    while(result[k]=='0') k++;
    if(k>size_result-1) printf("0");
    else{
        while(k>0){
            for(int i=1; i<=size_result; i++){
                result[i-1]=result[i];
            }
            k--;
        }
        printf("%s\n", result);
    }

}

int lecs_check(char* a, char*b, int size_a){
    int m,n;
    for(int i=0; i<=size_a; i++){
        m=a[i];
        n=b[i];
        if(m>n) return 1;
        else if(m<n) return -1;
    }
    return 0;
}

void sum(char* a, char *b, int size_a, int size_b){
    char* result=malloc(sizeof(char)*(size_a+3));
    int m,n,k;
    for(int i=0; i<=size_a+1; i++) result[i]='0';
    result[size_a+2]='\0';
    int d=abs(size_a-size_b);
    for(int i=0; i<=size_a; i++){
        n=a[size_a-i]-'0';
        if(i<=size_a-d){
            m=b[size_a-d-i]-'0';
            k=result[size_a+1-i]-'0';
            result[size_a+1-i]=k+n+m+'0';
        }
        else{
            m=result[size_a+1-i]-'0';
            result[size_a+1-i]=n+m+'0';
        }
        n=result[size_a+1-i]-'0';
        result[size_a-i]=n/10+'0';
        result[size_a+1-i]=n%10+'0';
    }
    output(result, size_a+3);
}

void razn(char* a, char *b, int size_a, int size_b){
    char* result=malloc(sizeof(char)*(size_a+1));
    int m,n,k,f;
    for(int i=0; i<=size_a; i++) result[i]='0';
    result[size_a+1]='\0';
    int d=abs(size_a-size_b);

    for(int i=0; i<=size_a; i++){
        n=a[size_a-i]-'0';
        if(i<=size_a-d){
            m=b[size_a-d-i]-'0';
            k=result[size_a-i]-'0';
            f=n-m+k;
            if(f<0){
                result[size_a-1-i]-=1;
                f+=10;
            }
            result[size_a-i]=f+'0';
        }
        else{
            m=result[size_a-i]-'0';
            result[size_a-i]=n+m+'0';
        }
    }
    output(result, size_a+1);
}

void multi(char* a, char *b, int size_a, int size_b){
    char* result=malloc(sizeof(char)*((size_a)*(size_b)+2));
    int m,n,k,f,len=(size_a)*(size_b);
    int d=0;
    for(int i=0; i<=len; i++) result[i]='0';
    result[len+1]='\0';
    for(int j=1; j<=size_b; j++){
        m=b[size_b-j]-'0';
        for(int i=1; i<=size_a; i++){
            n=(a[size_a-i]-'0')*m;
            k=result[len+1-d-i]-'0';
            f=result[len-d-i]-'0';
            result[len-d-i]=f+(k+n)/10+'0';
            result[len+1-d-i]=(k+n)%10+'0';
        }
        d++;
    }
    output(result, len+1);
}

void result(char* a, char* b, int size_a, int size_b, int zn){
    if(zn==1){
        if(size_a>=size_b) sum(a, b, size_a, size_b);
        else sum(b, a, size_b, size_a);
    }
    else if(zn==2){
        if(size_a-size_b<0) printf("-");

        if(size_a>size_b) razn(a, b, size_a, size_b);
        else if(size_a<size_b) razn(b, a, size_b, size_a);
        else if(lecs_check(a, b, size_a)==1) razn(a, b, size_a, size_a);
        else if(lecs_check(a, b, size_a)==-1){
            printf("-");
            razn(b, a, size_b, size_b);
        }
        else printf("0");
    }
    else if(zn==3){
        multi(a, b, size_a+1, size_b+1);
    }
}

int main(void)
{
    char* a= malloc(sizeof(char)*100001);
    char* b= malloc(sizeof(char)*100001);
    char c;
    int zn=0, temp=0;
    int size_a, size_b;
    c=getchar();
    while(!if_znak(c)){
        a[temp]=c;
        c=getchar();
        temp++;
    }
    a[temp]='\0';
    size_a=temp-1;
    zn=if_znak(c);
    c=getchar();
    temp=0;
    while((c!=EOF)&&(c!='\n')){
        b[temp]=c;
        c=getchar();
        temp++;
    }
    b[temp]='\0';
    size_b=temp-1;
    result(a, b, size_a, size_b, zn);
    return 0;
}
