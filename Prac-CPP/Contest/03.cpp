#include <iostream>
#include <iomanip>

using std::cin, std::cout, std::endl;

int main()
{
    cin.tie(nullptr);
    char tmp;
    bool fl = true;

    while (cin.get(tmp)) {
        if (fl && tmp != '0') {
            cout << tmp;
        } else if (fl && tmp == '0') {
            fl = false;
        } else if (!fl && tmp != '0') {
            cout << '0';
            cout << tmp;
            fl = true;
        }
    }
    if (!fl) {
        cout << '0';
    }
    cout << endl;
    return 0;
}
