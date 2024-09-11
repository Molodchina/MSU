#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char s[2000001];
int len;

int sdvig(char *result, int move){
    int i=0, k, j;
    while(i<len){
        move=i;
        k=i;
        j=i+1;
        while((j-1<2*len)&&(result[k]<=result[j])){
            result[k]<result[j]? k=i:k++;
            j++;
        }
        while(i<=k) i+=j-k;
    }
    return move;
}

int main(void)
{
    int move;
    scanf("%s", s);
    len=strlen(s);
    char *result=malloc(2*len+1);
    for(int i=0; i<len; i++) result[i]=s[i];
    for(int i=len; i<2*len; i++) result[i]=s[i-len];
    move=sdvig(result, 0);
    for(int i=move; i<len; i++) printf("%c", result[i]);
    for(int i=0; i<move; i++) printf("%c", result[i]);
    return 0;
}
