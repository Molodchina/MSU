#include <stdio.h>
#include <string.h>

char* fibonacci(char* s){
    int size=strlen(s), a=1, b=2, c, temp=0;
    char *r=(char *)malloc(sizeof(char)*size);
    for(int i=2; i<size; i++){
        if(i>b){
            c=a;
            a=b;
            b+=c;
        }
        if((i!=a)&&(i!=b)){
            r[temp]=s[i];
            ++temp;
        }
    }
    r[temp]='\0';
    free(s);
    for(int i=temp+1; i<size; i++){
        free(r[i]);
    }
    printf("%s\n", r);
    return 0;
}

int main(void){
    int size=10, i=0;
    char *s=(char *)malloc(sizeof(char)*size);
    char c=getchar();
    while((c!=EOF)&&(c!='\n')){
        if(i==size){
            size+=10;
            s=realloc(s, size);
        }
        s[i]=c;
        ++i;
        c=getchar();
    }
    s[i]='\0';
    s=fibonacci(s);
    return 0;
}
