#include <iostream>

using std::cin, std::cout, std::endl, std::hex;


int main()
{
    unsigned int offset = 0;
    unsigned int res = 0, temp;
    while(cin >> hex >> offset) {
        for (int i = 0; i < 4; ++i) {
            int len = 0;
            while (len < 4 && cin >> hex >> temp) {
                res <<= 8;
                res += temp;
                ++len;
            }
            if (len < 4) {
                return 0;
            } else {
                cout << res << endl;
            }
        }
    }
}
