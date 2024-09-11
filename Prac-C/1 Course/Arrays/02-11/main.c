#include <stdio.h>

int main(void)
{
    int board[11][11],x=0, y=0, amount=64;
    char s;
    for (int i=0; i<10; i++){
        for (int j=0; j<10; j++) board[i][j]=0;
    }
    while (1){
        s=getchar();
        if (s=='\n'){
            break;
        }
        else{
            switch (s){
                case 'a':
                    x=1;
                    break;
                case 'b':
                    x=2;
                    break;
                case 'c':
                    x=3;
                    break;
                case 'd':
                    x=4;
                    break;
                case 'e':
                    x=5;
                    break;
                case 'f':
                    x=6;
                    break;
                case 'g':
                    x=7;
                    break;
                case 'h':
                    x=8;
                    break;
                default:
                    break;
            }
            s=getchar();
            switch (s){
                case '1':
                    y=1;
                    break;
                case '2':
                    y=2;
                    break;
                case '3':
                    y=3;
                    break;
                case '4':
                    y=4;
                    break;
                case '5':
                    y=5;
                    break;
                case '6':
                    y=6;
                    break;
                case '7':
                    y=7;
                    break;
                case '8':
                    y=8;
                    break;
                default:
                    break;
            }
            for (int i=x-1; i<x+2; i++){
                for (int j=y-1; j<y+2; j++) board[i][j]=2;
            }
        }
    }
    for (int i=1; i<9; i++){
        for (int j=1; j<9; j++) if (board[i][j]==2) amount--;
    }
    printf("%d", amount);
    return 0;
}
