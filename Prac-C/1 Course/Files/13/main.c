#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>

typedef struct line {
    char *num[20];
} line;

line array[10000];
int m=0, a_col=0;
int type[20] = {0};

void del(char *head) {
    int le = 0;
    while (head[le] == ' ') {
        ++le;
    }
    int ri = strlen(head) - 1;
    while (head[ri] == ' ') {
        --ri;
    }
    for(int i = le; i <= ri; ++i) {
        head[i - le] = head[i];
    }
    head[ri - le + 1] = 0;
}

int comp(const void *fir, const void *sec){
    long long a=atoi(((line*)fir)->num[a_col]);
    long long b=atoi(((line*)sec)->num[a_col]);
    return a-b;
}

int compw(const void *fir, const void *sec) {
    char *a=((line*)fir)->num[a_col];
    char *b=((line*)sec)->num[a_col];
    return strcmp(a,b);
}

void output(int m, int k){
    for(int i = 0; i < m; ++i){
        for (int j = 0; j < k; ++j) {
            if (type[j] == 1)
                printf(j == k - 1 ? "%d\n": "%d;", atoi(array[i].num[j]));
            else
                printf(j == k - 1 ? "%s\n": "%s;", array[i].num[j]);
        }
    }
}

int fromFile(int inpt){
    if(inpt==0) return 0;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d", &a_col);
    char *r="";
    fgets(r, 2, stdin);
    int k = 0;
    r=";\n";
    char *arr = malloc(sizeof(char) * 2500);
    while (fgets(arr, 2500, stdin)) {
        k = 0;
        char *p = strtok(arr, r);
        while (p != NULL) {
            ((array[m]).num)[k] = p;
            del(array[m].num[k]);
            if (atoi(p)) {
                type[k] = 1;
            }
            ++k;
            p = strtok(NULL, r);
        }
        ++m;
        arr = malloc(sizeof(char) * 2500);
    }
    return k;
}

int main(void){
    int k=fromFile(1);
    if (type[a_col] == 1) {
        qsort(array, m, sizeof(line), comp);
    }
    else {
        qsort(array, m, sizeof(line), compw);
    }

    output(m, k);

    return 0;
}
