#include <iostream>

template<typename A>
auto process(const A &a) {
    typename A::value_type s = {};
    if (a.begin() == a.end())
        return s;
    size_t pos = 0;
    for (auto i = a.rbegin(); i != a.rend()
          && pos < 5; ++i, ++pos) {
        if (pos % 2 == 0) {
            s += *i;
        }
    }
    return s;
}
