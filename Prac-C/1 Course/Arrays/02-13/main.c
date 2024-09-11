#include <stdio.h>

int main(void)
{
    int a, b, n, m_col=0, l_col[102]={0}, board[9][9]={0}, column[9]={0};
    for (int i=1; i<9; i++){
        scanf("%d", &n);
        l_col[n]=i;
        board[0][i]=n;
    }
    for (int i=1; i<9; i++){
        scanf("%d", &n);
        column[i]=n;
        if (n>m_col) m_col=n;
    }
    for (int i=m_col+1; i<102; i++){
        if (l_col[i]>0){
            printf("-1");
            return 0;
        }
    }
    if (l_col[m_col]==0){
        printf("-1");
        return 0;
    }
    for (int i=1; i<9; i++){
        board[i][0]=column[i];
    }
    for (int i=1; i<9; i++){
        a=board[0][i];
        if (a>0){
            for (int j=1; j<9; j++){
                b=board[j][0];
                if (b>0){
                    if (b>a) b=a;
                    board[j][i]=b;
                }
            }
        }
    }
    n=0;
    for (int i=1; i<9; i++){
        for (int j=1; j<9; j++) if (board[i][j]>0) n+=board[i][j];
    }
    printf("%d", n);
    return 0;
}
