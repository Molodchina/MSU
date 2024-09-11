#include <stdio.h>

char temp[5][5];
int k=0;

void bin(char s){
    if (s=='a'){
        temp[k][0]='1';
        temp[k][1]='0';
        temp[k][2]='1';
        temp[k][3]='0';
    }
    else if (s=='b'){
        temp[k][0]='1';
        temp[k][1]='0';
        temp[k][2]='1';
        temp[k][3]='1';
    }
    else if (s=='c'){
        temp[k][0]='1';
        temp[k][1]='1';
        temp[k][2]='0';
        temp[k][3]='0';
    }
    else if (s=='d'){
        temp[k][0]='1';
        temp[k][1]='1';
        temp[k][2]='0';
        temp[k][3]='1';
    }
    else if (s=='e'){
        temp[k][0]='1';
        temp[k][1]='1';
        temp[k][2]='1';
        temp[k][3]='0';
    }
    else if (s=='f'){
        temp[k][0]='1';
        temp[k][1]='1';
        temp[k][2]='1';
        temp[k][3]='1';
    }
    else if (s=='9'){
        temp[k][0]='1';
        temp[k][1]='0';
        temp[k][2]='0';
        temp[k][3]='1';
    }
    else if (s=='8'){
        temp[k][0]='1';
        temp[k][1]='0';
        temp[k][2]='0';
        temp[k][3]='0';
    }
    else if (s=='7'){
        temp[k][0]='0';
        temp[k][1]='1';
        temp[k][2]='1';
        temp[k][3]='1';
    }
    else if (s=='6'){
        temp[k][0]='0';
        temp[k][1]='1';
        temp[k][2]='1';
        temp[k][3]='0';
    }
    else if (s=='5'){
        temp[k][0]='0';
        temp[k][1]='1';
        temp[k][2]='0';
        temp[k][3]='1';
    }
    else if (s=='4'){
        temp[k][0]='0';
        temp[k][1]='1';
        temp[k][2]='0';
        temp[k][3]='0';
    }
    else if (s=='3'){
        temp[k][0]='0';
        temp[k][1]='0';
        temp[k][2]='1';
        temp[k][3]='1';
    }
    else if (s=='2'){
        temp[k][0]='0';
        temp[k][1]='0';
        temp[k][2]='1';
        temp[k][3]='0';
    }
    else if (s=='1'){
        temp[k][0]='0';
        temp[k][1]='0';
        temp[k][2]='0';
        temp[k][3]='1';
    }
    else if (s=='0'){
        temp[k][0]='0';
        temp[k][1]='0';
        temp[k][2]='0';
        temp[k][3]='0';
    }
    k++;
}


void back(char m[5][5]){
    char x[5];
    for (int i=0; i<4; i++) x[i]='0';
    int a, n;
    for (int line=0; line<4; line++){
        a=0;
        n=1;
        for (int j=0; j<4; j++){
            if (m[line][3-j]=='1') a+=n;
            n*=2;
        }
        if (a==10) x[line]='a';
        else if (a==11) x[line]='b';
        else if (a==12) x[line]='c';
        else if (a==13) x[line]='d';
        else if (a==14) x[line]='e';
        else if (a==15) x[line]='f';
        else if (a==9) x[line]='9';
        else if (a==8) x[line]='8';
        else if (a==7) x[line]='7';
        else if (a==6) x[line]='6';
        else if (a==5) x[line]='5';
        else if (a==4) x[line]='4';
        else if (a==3) x[line]='3';
        else if (a==2) x[line]='2';
        else if (a==1) x[line]='1';
        else if (a==0) x[line]='0';
    }
    printf("%.4s", x);
}

int main(void)
{
    char s[5];
    char mas[5][5];
    scanf("%s", s);
    for (int i=0; i<4; i++) bin(s[i]);
    for (int i=0; i<4; i++){
        for (int j=0; j<5; j++){
            if (j==4) mas[i][j]='\n';
            else mas[i][j]='0';
        }
    }
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            if (temp[i][j]=='0') mas[i][j]='0';
            else mas[i][j]='1';
        }
    }
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            if (temp[i][j]=='0') mas[j][i]='0';
            else mas[j][i]='1';
        }
    }
    back(mas);
    return 0;
}
