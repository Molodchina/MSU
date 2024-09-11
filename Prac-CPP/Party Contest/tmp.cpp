#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <map>
#include <functional>
#include <sstream>


using std::string, std::cout, std::endl, std::cin,
        std::vector, std::stringstream, std::getline;

int main() {

    int k, n, a, b, minDist, minj;

    cin >> n;

    int m[n][n];
    int col[n];
    int ostov[n];
    int P[n];

    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            cin >> m [i] [j];
            if (m[i][j]==0)
                m[i][j]=1000000;
        }
    }

    cin >> a;
    a--;

    cin >> b;
    b--;

    for (int i=0; i<n; i++){
        ostov [i]=m[a][i];
        col[i]=1;
        P[i]=1000000;
    }

    ostov[a]=0;
    col[a]=0;

    for (int i=0; i<n-1; i++){
        minDist=1000000;
        for (int j=0; j<n; j++)
            if ((col[j]==1)&&(ostov[j]<minDist)){
                minDist=ostov[j];
                minj=j;
            }
        col[minj]=0;
        for ( int j=0; j<n; j++ ){
            if (ostov[j]>ostov[minj] + m[minj][j]){
                ostov[j]=ostov[minj] + m[minj][j];
            }
        }
    }

    minj=b;
    k=0;
    while (minj!=a){
        for (int j=0; j<n; j++){
            if ((m[minj][j]!=100000)&&(m[minj][j]+ostov[j]==ostov[minj])){
                P[k]=minj+1;
                minj=j;
                k++;
            }
        }
    }
    P[k]=a+1;

    cout << ostov[b] << endl;

    for (int i=k; i>=0; i--)
        cout << P[i] << ' ';

    return 0;
}
