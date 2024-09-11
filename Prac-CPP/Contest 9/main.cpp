#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using std::string, std::cin, std::cout, std::endl,
    std::istringstream, std::any_of, std::all_of, std::none_of;


int main() {
    string l, r;
    bool s{}, fullterm_l{}, sr{}, except{};
    bool cf = true;
    bool short_cf = true;
    while(cin >> l >> r) {
        if (l == "S")
            s = true;
        if (none_of(l.begin(), l.end(),
                    [](char c) { return c >= 'A' && c <= 'Z'; } ))
            fullterm_l = true;
        if (any_of(r.begin(), r.end(), [](char c) { return c == '_'; })) {
            if (l == "S")
                except = true;
            else
                short_cf = false;
        }
        if (l.size() > r.size())
            short_cf = false;
        if (fullterm_l || l.size() != 1)
            cf = false;
        if (any_of(r.begin(), r.end(), [](char c) { return c == 'S'; }))
            sr = true;
    }

    if (except && sr)
        short_cf = false;
    if (fullterm_l || !s)
        cout << -1 << endl;
    else if (cf) {
        if (short_cf)
            cout << 23 << endl;
        else
            cout << 2 << endl;
    } else {
        cout << 10 << endl;
    }


    return 0;
}
