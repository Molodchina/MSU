#include <iostream>
#include <vector>

template<typename A, typename F>
auto myapply(A begin, A end, F f) {
    for (auto i = begin; i != end; ++i) {
        f(*i);
    }
}

template<typename A, typename P>
auto myfilter2(A begin, A end, P p) {
    std::vector<std::reference_wrapper<typename std::iterator_traits<A>::value_type>> v;
    for (auto i = begin; i != end; ++i) {
        if (p(*i))
            v.push_back(*i);
    }

    return v;
}
