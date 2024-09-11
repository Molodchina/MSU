#include <iostream>
#include <string>

using std::cin, std::cout, std::endl;

class BinaryNumber
{
public:
    BinaryNumber(const std::string &str = "") {
        len = size(str);
        s.resize(len);
        for (size_t i = 0; i < len; ++i) {
            s[i] = str[i];
        }
    }
    operator std::string () const {
        return s;
    }
    const BinaryNumber &operator++ () {
        bool fl = true;
        long i = len - 1;
        while (i >= 0) {
            if (s[i] == '0') {
                s[i] = '1';
                fl = false;
                break;
            } else if (s[i] == '1') {
                s[i] = '0';
            }
            --i;
        }
        if (fl) {
            s[0] = '0';
            s.insert(s.begin(), '1');
            ++len;
        }
        return *this;
    }
private:
    std::string s;
    size_t len;
};
