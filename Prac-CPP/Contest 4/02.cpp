#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdint>

using std::cin, std::cout, std::endl;

void
process(std::vector<int64_t> &v,
        int64_t val)
{
    size_t len = 0;
    for (auto i = v.rbegin();
         i < v.rend(); ++i) {
        if (*i >= val) {
            ++len;
        }
    }
    v.reserve(v.size() + len);
    for (auto i = v.rbegin();
         i < v.rend(); ++i) {
        if (*i >= val) {
            v.push_back(*i);
        }
    }
}
