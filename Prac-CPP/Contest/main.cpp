#include <iostream>
#include <string>
#include <vector>

using std::cin, std::cout, std::endl, std::string, std::stol, std::vector;

class Matrix{
public:
    Matrix() {
        m.resize(max_val);
        for (auto i: m) {
            i.resize(max_val);
        }
    }

    long &operator[] (int row, int col) {
        if (row >= max_val || col >= max_val) {
            cout << "Position err" << endl;
        }
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
    const int max_val = 3;
};

int main() {
    Matrix m;
    m[1, 1] = 5;

    for (const auto &row : m) {
        for (auto cell : row) {
            cout << cell << " ";
        }
        cout << "\n";
    }
}
