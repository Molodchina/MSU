#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>
#include <cstdint>

// Рекурсивная функция r производит необходимые вычисления,
// результат вычисления передается с помощью исключения,
// которое является типом R (хранит long), с функцией val(),
// возвращающей хранящаесе значение


using std::string, std::cin, std::cout, std::endl, std::exception;


class R
{
    long _r;
public:
    R(const long &r = 0): _r(r) {};
    const long &val () {
        return _r;
    }
};


void r (unsigned long a, unsigned long b, unsigned int k)
{
    if (k == 0) {
        R r((long) (a + b));
        throw r;
    }
    if (b == 1) {
        R r((long) a);
        throw r;
    }
    try {
        r(a, b - 1, k);
    } catch (R res) {
        try {
            r(a, res.val(), k - 1);
        } catch (R result) {
            throw result;
        }
    }
}


int main()
{
    unsigned long a, b;
    unsigned int k;

    while (cin >> a >> b >> k) {
        try {
            r(a, b, k);
        } catch (R r) {
            cout << r.val() << endl;
        }
    }
    return 0;
}