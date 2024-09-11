#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>


void
process(const std::vector<int> &v1,
        std::vector<int> &v2)
{
    std::vector<int> new_v1(v1);
    std::sort(new_v1.begin(), new_v1.end());
    auto last = std::unique(new_v1.begin(), new_v1.end());
    new_v1.erase(last, new_v1.end());

    auto cur = v2.begin();
    size_t pos = 0;
    size_t max_pos = v2.size();

    for (auto i = new_v1.begin(); i < new_v1.end()
                                  && !v2.empty(); ++i) {
        if (*i < 0) {
            continue;
        }
        if ((size_t) *i >= max_pos) {
            break;
        }
        while (true) {
            if ((uint64_t) *i == pos) {
                auto del = cur;
                ++pos;
                v2.erase(del);
                break;
            } else {
                ++cur;
                ++pos;
            }
        }
    }
}



int main()
{
    std::vector<int> v2 = {1, 2, 3, 4, 5};
    std::vector<int> v1 = {1, 3, 3, 1, -1, -1,0, 100};
    process(v1, v2);
    for (auto i = v2.begin(); i < v2.end(); ++i) {
        std::cout << *i << std::endl;
    }
}
