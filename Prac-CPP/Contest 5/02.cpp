#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using std::cin, std::cout, std::endl, std::string, std::map, std::vector;


int main()
{
    map<std::string, vector<int>> m{};
    string tmp_n;
    int tmp_g;
    while(cin >> tmp_n >> tmp_g) {
        vector<int> v = {};
        if (!m.contains(tmp_n)){
            v.push_back(tmp_g);
            m.insert(std::pair<string, vector<int>>(tmp_n, v));
        }
        else{
            v = m[tmp_n];
            v.push_back(tmp_g);
            m[tmp_n] = v;
        }
    }

    for (auto i: m) {
        double sum{};
        for (auto j : i.second)
            sum += j;
        std::cout << i.first << ' ' << sum / i.second.size() << std::endl;
    }
}
