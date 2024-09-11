#include <iostream>
#include <map>
#include <vector>
#include <cstdint>

using std::cin, std::cout, std::endl, std::string, std::map, std::vector, std::pair;



int main ()
{
    map<u_int32_t, map<u_int32_t, u_int64_t>> m;

    u_int64_t mod = 4294967161;
    u_int32_t r, c;
    u_int64_t v;
    while (cin >> r >> c >> v) {
        if (v == mod && r == 0 && c == 0) {
            break;
        }
        m[c][r] = v % mod;
    }

    map<pair<u_int32_t, u_int32_t>, u_int64_t> res;
    while (cin >> r >> c >> v) {
        for (const auto &i: m[r]) {
            res[pair(i.first, c)] = (res[pair(i.first, c)] +
                                     (i.second * (v % mod)) % mod) % mod;
        }
    }

    for (auto i: res) {
        if (i.second)
            cout << i.first.first << ' ' << i.first.second << ' '
                 << i.second % mod << endl;
    }

    return 0;
}