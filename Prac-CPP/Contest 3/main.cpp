#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "cmc_complex.h"
#include "cmc_complex_stack.h"
#include "cmc_complex_eval.h"

using std::stod, std::stoll, std::vector,
        std::cout, std::endl, std::string, numbers::complex, numbers::complex_stack,
                numbers::eval;

int main (int argc, char*argv[])
{
    const complex c(argv[1]);
    const double r = stod(argv[2]);
    const long long n = stoll(argv[3]);
    if (n == 0 || r < __DBL_EPSILON__) {
        cout << "(0,0)" << endl;
        return 0;
    }

    vector<string> expr{};
    for (int i = 4; i < argc; ++i) {
        expr.emplace_back(argv[i]);
    }

    complex res;
    const double step = 2 * M_PI / n;
    complex last(c.re() + r, c.im());
    for (long long i = 1; i <= n; ++i) {
        complex z;
        double angle = (double) i * step;
        z = c + complex(r * cos(angle), r * sin(angle));
        res += eval(expr, last) * (z - last);
        last = z;
    }
    cout << res.to_string() << endl;

    return 0;
}
