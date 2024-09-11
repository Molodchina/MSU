#include <string>
#include <iostream>
#include <string>

using std::string, std::cin, std::cout, std::endl;


// S -> aA
// A -> Sd | Bd
// B -> bC
// C -> Bc | c


void S(int, int);
void A(int, int);
void B(int);
void C(int);

void S(int n, int f) {
    cout << 'a';
    A(n - 2, f);
}

void A(int n, int f) {
    if (n > 0)
        S(n, f);
    else
        B(f);
    cout << 'd';
}

void B(int f) {
    cout << 'b';
    C(f - 2);
}

void C(int f) {
    if (f > 0)
        B(f);
    cout << 'c';
}


int main()
{
    int n;
    cin >> n;
    if (n < 4 || n % 2) {
        return 0;
    }

    for (int i = n - 2; i > 0; i -= 2) {
        S(i, n - i);
        cout << endl;
    }
    return 0;
}