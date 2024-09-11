#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *in, *out;
char *s;
int len;

void output(long long b){
    fprintf(out, "%lld", b);
    fclose(in);
    fclose(out);
}

char *s_in(FILE* in, size_t size){
    char *str;
    int ch;
    size_t len = 0;
    str = malloc(sizeof(char)*size);
    if(!str) return str;
    ch=fgetc(in);
    while((EOF!=ch)&&(ch!='\n')){
        str[len++]=ch;
        if(len==size){
            size+=16;
            str=realloc(str, sizeof(char)*size);
            if(!str) return str;
        }
        ch=fgetc(in);
    }
    ++len;
    str[len] = '\0';
    return realloc(str, sizeof(char)*len);
}

void find_s(long long b, char *p){
    long long a;
    char c;
    while(p!=&s[len-1]+1) {
        while(p[0]==' ') p++;
        c=p[0];
        p++;
        a=strtoll(p, &p, 10);
        if(c=='+') b+=a;
        else b-=a;
    }
    output(b);
    return;
}

int main(void){
    long long b;
    char *p;

    in=fopen("input.txt", "r");
    out=fopen("output.txt", "w");

    s=s_in(in, 10);
    len=strlen(s);
    b=strtoll(s, &p, 10);

    find_s(b, p);
    return 0;
}
