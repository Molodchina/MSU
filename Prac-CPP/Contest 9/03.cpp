#include <string>
#include <iostream>
#include <string>

using std::string, std::cin, std::cout, std::endl;

// S -> AB
// A -> aAb | ab
// B -> 0B1 | 01
// b0 -> 0b

bool ch(string s) {
    size_t pos{}, a_len{}, b_len{}, z_len{}, o_len{};
    size_t len = s.size();

    for (; pos < len && s[pos] == 'a'; ++pos, ++a_len) {}
    for (; pos < len && s[pos] == '0'; ++pos, ++z_len) {}
    for (; pos < len && s[pos] == 'b'; ++pos, ++b_len) {}
    for (; pos < len && s[pos] == '1'; ++pos, ++o_len) {}

    return pos == len && a_len == b_len && z_len == o_len
           && a_len > 0 && z_len > 0;
}

int main() {
    string s;
    while (getline(cin, s)) {
        cout << ch(s) << endl;
    }

    return 0;
}
