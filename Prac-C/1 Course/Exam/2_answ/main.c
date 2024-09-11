#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* fibocci(char* s){
    int size=strlen(s), a=1, b=2, c, temp=0;
    char *r=(char *)malloc(sizeof(char)*(temp+1));
    for(int i=2; i<size; i++){
        if(i>b){
            c=a;
            a=b;
            b+=c;
        }
        if((i!=a)&&(i!=b)){
            r[temp]=s[i];
            ++temp;
            r=(char *)realloc(r, sizeof(char)*(temp+1));
        }
    }
    r[temp]='\0';
    free(s);
    return r;
}
