#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <map>
#include <functional>
#include <array>
#include <sstream>


using std::string, std::cout, std::endl, std::cin, std::pair, std::stoi,
        std::vector, std::stringstream, std::getline, std::array;

pair<pair<int, int>, pair<int, int>> parse(const string& s) {
    bool h1{}, m1{};
    pair<int, int> start, end;
    string tmp;
    for(char c: s) {
        cout << tmp << endl;
        if (c == ':') {
            if (!h1) {
                start.first = stoi(tmp);
                tmp.clear();
                h1 = true;
            } else {
                end.first = stoi(tmp);
                tmp.clear();
            }
            continue;
        }
        if (c == '-') {
            if (!m1) {
                start.second = stoi(tmp);
                tmp.clear();
                m1 = true;
            } else {
                end.second = stoi(tmp);
                tmp.clear();
            }
            continue;
        }
        tmp.push_back(c);
    }

    cout << start.first << ' ' << start.second << endl;
    cout << end.first << ' ' << end.second << endl;
    return {start, end};
}

int main() {
    int n, m;
    cin >> n >> m;
    array<int, 1440> a{};
    for (int meet = 0; meet < m; ++meet) {
        string s;
        char c;
        cin >> c >> s;
        auto [start, end] = parse(s);

    }

    return 0;
}
