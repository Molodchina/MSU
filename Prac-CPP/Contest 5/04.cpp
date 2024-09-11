#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using std::cin, std::cout, std::endl, std::string, std::map, std::vector;



int main ()
{
    long long mod = 4294967161;

    map<std::pair<unsigned int,unsigned int>, long long> m{};

    unsigned int r, c;
    long long v;
    while (cin >> r >> c >> v) {
        if (v == mod && r == 0 && c == 0)
            continue;
        m[std::make_pair(r,c)] += v;
    }

    for (auto i: m) {
        if (long long res = i.second % mod; res != 0){
            cout << i.first.first << ' ' << i.first.second << ' '
                 << res << endl;
        }
    }

    return 0;
}