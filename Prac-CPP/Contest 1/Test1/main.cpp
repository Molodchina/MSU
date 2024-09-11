#include <iostream>
#include <iomanip>

int main()
{
    int c;
    using std::cout, std::cin, std::endl;

    while (cin >> c) {
        cout << "(" << c + c << ")" << endl;
    }
}