#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>
#include <cstdint>

using std::string, std::cin, std::cout, std::endl, std::exception;


class S
{
    int _v{};
    bool _f{};
    bool _p{};
public:
    S() {
        if (cin >> _v) {
            _f = true;
            _p = true;
        }
    }
    S(S &&s) : S() {
        if (s._f) {
            _v += s._v;
            if (_f)
                s._p = false;
        }
    }
    ~S() {
        if (_p)
            cout << _v << endl;
    }
    operator bool() const {
        return _f;
    }
};