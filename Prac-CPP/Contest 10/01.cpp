#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using std::string, std::cin, std::cout, std::endl,
        std::istringstream, std::any_of, std::all_of, std::none_of;

bool non_term(char c) {
    return c >= 'A' && c <= 'Z';
}

bool is_eps(string s) {
    return any_of(s.begin(), s.end(), [](char c) { return c == '_'; });
}

int main() {
    string r;
    char l;
    bool short_cf = true;
    bool l_reg = true;
    bool r_reg = true;
    bool l_au = true;
    bool r_au = true;
    bool sr{}, s_eps{};
    while(cin >> l >> r) {
        if (is_eps(r)) {
            if (l == 'S')
                s_eps = true;
            else {
                short_cf = false;
            }
        }

        if (any_of(r.begin(), r.end(),
                   [](char c) { return c == 'S'; }))
            sr = true;

        {
            size_t i{}, j{}, n{}, m{};
            while(i < r.size() && !non_term(r[i])) {
                ++i;
            }
            while(j + i < r.size() && non_term(r[j + i])) {
                ++j;
            }
            while(n + j + i < r.size() && !non_term(r[n + j + i])) {
                ++n;
            }
            while(m + n + j + i < r.size() && non_term(r[m + n + j + i])) {
                ++m;
            }
            if (m) {
                l_reg = l_au = r_reg = r_au = false;
                continue;
            }

            if (i > 1 || n > 1)
                l_au = r_au = false;

            if (j) {
                if (i & n || j > 1)
                    l_reg = l_au = r_reg = r_au = false;
                else if (i)
                    l_reg = l_au = false;
                else if (n)
                    r_reg = r_au = false;
            }
        }
    }

    if (!short_cf || (sr && s_eps)) {
        l_au = r_au = false;
    }

    if (l_au) {
        cout << 311 << endl;
    } else if (r_au) {
        cout << 321 << endl;
    } else if (l_reg) {
        cout << 31 << endl;
    } else if (r_reg) {
        cout << 32 << endl;
    } else if (short_cf)
        cout << 21 << endl;
    else
        cout << 2 << endl;

    return 0;
}
