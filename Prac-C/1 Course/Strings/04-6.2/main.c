#include <stdio.h>

char a[10000001];
int amount=0, add;

void output(int temp_c, int temp_o){
    int current=0;
    for(int i=0; i<amount; i++){
        if(a[i]==' '){
            current++;
            add=temp_c+1;
            if(current<=temp_o) add++;
            for(int j=0; j<add; j++) printf(" ");
        }
        else printf("%c", a[i]);
    }
}

int main(void)
{
    int n;
    char c;
    int temp_c=0, temp_o=0, spaces=0;
    scanf("%d", &n);
    c=getchar();
    while(1){
        c=getchar();
        if ((c=='\n')||(c==EOF)) break;
        else{
            a[amount]=c;
            if(c==' ') spaces++;
            amount++;
        }
    }
    if (amount==n){
        printf("%s", a);
        return 0;
    }
    add=n-amount;
    temp_c=add/spaces;
    temp_o=add%spaces;
    output(temp_c, temp_o);
    return 0;
}
