#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int len=0, a_col=0, col=0;

typedef struct line{
    char *current[20][101];
} line;

line lines[10000];
char type[20];

int if_d(int k, int j){
    if(atoi(lines[k].current[a_col])>atoi(lines[j].current[a_col])){
        return 1;
    }
    return 0;
}

int if_ch(int k, int j){
    if((strcmp(lines[k].current[a_col], lines[j].current[a_col]) > 0)&&(strlen(lines[k].current[a_col])==strlen(lines[j].current[a_col]))){
        return 1;
    }
    else if(strlen(lines[k].current[a_col])>strlen(lines[j].current[a_col])){
        return 1;
    }
    return 0;
}

void sr(int n){
    line tmp;
    for(int i=0; i<len-1; i++){
       for(int j=len-1; j>i; j--){
           if(atoi(lines[0].current[a_col])==0? if_ch(j-1, j) : if_d(j-1, j)){
                tmp = lines[j-1];
                lines[j-1] = lines[j] ;
                lines[j] = tmp;
           }
        }
    }
}

void fromFile(int size){
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int i=0, j=0, k=0, fl=0;
    char c;
    scanf("%d", &a_col);
    scanf("%c", &c);
    while (scanf("%c", &c) != EOF) {
        if(c=='\n'){
            i++;
            j=0;
            k=0;
            continue;
        }
        if(c=='"') fl*=-1;
        if(fl){
            lines[i].current[j][k]=c;
            k++;
        }
        else{
            if(c!=' '){
                if(c==';'){
                    if(atoi(lines[i].current[j])) type[j]='i';
                    j++;
                    k=0;
                }
                else{
                    lines[i].current[j][k]=c;
                    k++;
                }
            }
        }
    }
    col=j;
    len=i+1;
}

int comp(const void *fir, const void *sec) {
    return (atoi(((line*)fir)->current[a_col]) -
            atoi(((line*)sec)->current[a_col]));
}

int compw(const void *fir, const void *sec) {
    return strcmp(((line*)fir)->current[a_col],
                  ((line*)sec)->current[a_col]);
}

void output(int len){
    char *s;
    int k=col;
    for(int i=0; i<len; ++i){
        for(int j=0; j<=k; ++j){
            s=lines[i].current[j];
            if (type[j]=='i') {
                printf(j==k? "%d\n": "%d;", atoi(s));
            }
            else {
                printf(j==k ? "%s\n": "%s;", s);
            }
        }
    }
}

int main(void){
    for(int i=0; i<20; i++) type[i]='s';
    fromFile(101);
    if(type[a_col] == 'i') {
        qsort(lines, len-1, sizeof(line), comp);
    }
    else {
        qsort(lines, len-1, sizeof(line), compw);
    }
    //output(len);
    for(int i = 0; i < len; ++i) {
        for (int j = 0; j < col; ++j) {
            char *now = lines[i].current[j];
            //printf("%d\n", matrix[i][j]);
            if (type[j] == 'i') {
                //aprintf("%d\t ", atoi(now));
                fprintf(output, j == col - 1 ? "%d\n": "%d;", atoi(now));
            }
            else {
                //strip(now);
                //aprintf("(%s) (%d)\t ", now, strlen(now));
                fprintf(output, j == col - 1 ? "%s\n": "%s;", now);
            }
        }
            //aprintf("\naaa\n");
    }
    return 0;
}
