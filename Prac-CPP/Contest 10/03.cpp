#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>

using std::string, std::cin, std::cout, std::endl, std::map,
        std::vector, std::pair, std::all_of, std::any_of, std::priority_queue;

struct A
{
    string c;
    char a;
    string n;
};

void parse(map<string, map<char, string>> v, vector<string> e, const string &b, string s) {
    bool f = true;
    size_t i = 0;
    if (!v.contains(b)) {
        cout << 0 << endl << 0 << endl << b << endl;
        return;
    }
    auto cur = v[b];
    string prev = b;
    while(f) {
        if (cur.contains(s[i])) {
            prev = cur[s[i]];
            ++i;
            if (i >= s.size())
                break;
            cur = v[prev];
        } else {
            f = false;
        }
    }

    if (f) {
        f = any_of(e.begin(), e.end(),
                   [&prev](const string &str) { return str == prev; });
    }

    cout << f << endl << i << endl << prev << endl;
}

int main() {
    map<string, map<char, string>> v;
    {
        string c, n;
        char a;
        while (cin >> c) {
            if (c == "END")
                break;
            cin >> a >> n;
            v[c][a] = n;
        }
    }
    vector<string> e;
    {
        string s;
        while (cin >> s && s != "END")
            e.push_back(s);
    }
    string b, s;
    cin >> b >> s;

    parse(v, e, b, s);

    return 0;
}
