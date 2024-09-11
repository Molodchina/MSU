#include <bits/stdc++.h>

using namespace std;

void f(int) {
    cout << __PRETTY_FUNCTION__ << endl;
}
void f(double) {
    cout << __PRETTY_FUNCTION__ << endl;
}

int main()
{
    int i = 1;
    double ci = 2;
    f(i);
    f(ci);

    return 0;
}

