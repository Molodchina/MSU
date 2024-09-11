#include <iostream>

template<typename A, typename P>
auto myfilter(A a, P p) {
    A res;
    for (auto i: a) {
        if (p(i))
            res.insert(res.end(), i);
    }
    return res;
}
