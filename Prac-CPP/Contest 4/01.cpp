#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdint>

using std::cin, std::cout, std::endl;

void
process(const std::vector<uint64_t> &v1,
        std::vector<uint64_t> &v2, long step)
{
    auto j = v2.rbegin();
    for (auto i = v1.begin(); j < v2.rend()
                              && i < v1.end(); i += step, ++j) {
        *j += *i;
    }
}

