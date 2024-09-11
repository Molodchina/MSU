#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>
#include <cstdint>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <complex>
#include <array>

using std::array, std::pair, std::vector, std::complex, std::norm;

namespace Equations
{
    using namespace std::complex_literals;

    template<class T>
    pair<bool, vector<complex<T>>>
    quadratic (array<complex<T>, 3> v) {
        const T EPS = 32 * std::numeric_limits<T>::epsilon();
        const complex<T> k1 =  (complex<T>) (4.0 + 0i);
        const complex<T> k2 = (complex<T>) (2.0 + 0i);
        if (norm(v[2]) < EPS) {
            if (norm(v[1]) < EPS) {
                if (norm(v[0]) < EPS)
                    return {false, {}};
                return {true, {}};
            }
            return {true, {-v[0] / v[1]}};
        }
        const complex<T> root_d = sqrt(v[1] * v[1] - k1 * v[0] * v[2]);
        return {true, {(-v[1] + root_d) / (k2 * v[2]),
                       (-v[1] - root_d) / (k2 * v[2])}};
    }
}
