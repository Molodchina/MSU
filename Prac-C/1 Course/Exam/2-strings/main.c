#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sr(char *s1, char *s2){
    int l1=strlen(s1)-1;
    int l2=strlen(s2)-1;
    int d=l1-l2;
    if(d>=0){
        for(int i=l1; i>=d; i--){
            int j=s1[i]-s2[i-d];
            if(j>0) return -1;
            else if(j<0) return 1;
        }
    }
    if(d<0){
        for(int i=l2; i>=d; i--){
            int j=s1[i-d]-s2[i];
            if(j>0) return -1;
            else if(j<0) return 1;
        }
    }
    return 0;
}

int main(void){
    char *s1=malloc(sizeof(char)*1001);
    char *s2=malloc(sizeof(char)*1001);
    int j=-1;
    char x;
    x=getchar();
    while(x!='\n'){
        s1[++j]=x;
        x=getchar();
    }
    s1[j+1]='\0';
    j=-1;
    x=getchar();
    while(x!='\n'){
        s2[++j]=x;
        x=getchar();
    }
    s2[j+1]='\0';
    if(sr(s1,s2)>=0){
        puts(s1);
        puts(s2);
        free(s1);
        free(s2);
        return 0;
    }
    puts(s2);
    puts(s1);
    free(s1);
    free(s2);
    return 0;
}
