#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct line{
    char string[501];
    char sr[101];
} line;

int main(void){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    line* lines=malloc(sizeof(line)*10000);
    int n;
    char c;
    scanf("%d", &n);
    scanf("%c", &c);
    int i, j =0;
    while(scanf("%c", &c)!=EOF){
        if(c=='\n'){
            i++;
            j=0;
            continue;
        }
        if(c!=' '){
            lines[i].string[j]=c;
            j++;
        }
    }
    int len=i+1;
    for(int i=0; i<len; i++)
        printf("%s\n", lines[i].string);
    return;
}
