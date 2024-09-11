#include <iostream>
#include <string>

using std::cin, std::cout, std::endl, std::string, std::hex;

int main()
{
    cin.tie(nullptr);
    char tmp, prev = '\0';
    size_t len = 0;
    while(cin.get(tmp)) {
        if (len == 0) {
            ++len;
            prev = tmp;
            continue;
        }
        if (prev == tmp) {
            ++len;
        } else {
            if (len > 4 || prev == '#') {
                cout << '#';
                cout << prev;
                cout << hex << len;
                cout << '#';
            } else {
                for(size_t j = 0; j < len; ++j) {
                    cout << prev;
                }
            }
            len = 1;
            prev = tmp;
        }
    }
    if (len > 4 || prev == '#') {
        cout << '#';
        cout << prev;
        cout << hex << len;
        cout << '#';
    } else {
        for(size_t j = 0; j < len; ++j) {
            cout << prev;
        }
    }
    return 0;
}
