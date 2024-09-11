#include <iostream>
#include <vector>
#include <algorithm>

using std::cout, std::endl;

template<typename A, typename B>
auto myremove(A begin, A end, B start, B finish) {
    std::vector nums(begin, end);
    std::sort(nums.begin(), nums.end());
    auto last = std::unique(nums.begin(), nums.end());

    size_t max_pos = 0;
    for (auto i = start; i != finish; ++i) {
        ++max_pos;
    }

    size_t pos = 0;
    auto rm = start;
    for (auto it2 = start; it2 != finish; ++it2, ++pos) {
        bool fl = true;
        for (auto j = nums.begin(); j != last; ++j) {
            if (*j < 0)
                continue;
            else if (*j > (int) max_pos) {
                last = j;
                break;
            }
            else if (*j == (int) pos) {
                fl = false;
                break;
            }
        }
        if (fl) {
            *rm++ = std::move(*it2);
        }
    }
    return rm;
}
