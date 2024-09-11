#include <iostream>
#include <string>
#include <vector>

using std::cin, std::cout, std::endl, std::string, std::stol, std::vector;

class Matrix{
public:
    Matrix() {
        m.resize(max_val);
        for (size_t i = 0; i < max_val; ++i) {
            m[i].resize(max_val);
        }
    }

    long &operator[] (int row, int col) {
        return m[row][col];
    }

    auto begin() {
        return m.begin();
    }

    auto end() {
        return m.end();
    }
private:
    vector<vector<int64_t>> m{};
    const size_t max_val = 3;
};
