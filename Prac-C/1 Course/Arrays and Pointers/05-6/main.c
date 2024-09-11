#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int flag=0, n;
    char* p=NULL;
    scanf("%d", &n);
    p=(char*) malloc(sizeof(char)*n);
    for(int i=0; i<n; i++) scanf("%c", p[i]);
    for(int i=0; i<=n/2; i++){
        if(p[i]!=p[n-1-i]) flag=1;
    }
    if(flag) printf("NO");
    else printf("YES");
    free(p);
    return 0;
}
