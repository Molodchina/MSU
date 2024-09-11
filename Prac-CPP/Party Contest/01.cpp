#include <bits/stdc++.h>

using namespace std;

vector<int> more(vector<int> v, vector<int> s, size_t pos, bool f) {
    for (size_t i = pos; i < s.size(); ++i) {
        int sum = s[i] + (int) f;
        if (sum / 10) {
            sum %= 10;
            f = true;
        } else {
            f = false;
        }
        v.push_back(sum);
    }
    if (f)
        v.push_back(1);
    return v;
}

int
main()
{
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    reverse(s1.begin(), s1.end());
    reverse(s2.begin(), s2.end());
    vector<int> v1, v2;
    for (auto i: s1) {
        if (isdigit(i))
            v1.push_back(i - '0');
    }
    for (auto i: s2) {
        if (isdigit(i))
            v2.push_back(i - '0');
    }

    vector<int> v;
    bool f{};
    size_t i = 0;
    for(; i < v1.size() && i < v2.size(); ++i) {
        int s = v1[i] + v2[i] + (int) f;

        if (s / 10) {
            s %= 10;
            f = true;
        } else {
            f = false;
        }
        v.push_back(s);
    }

    if (v1.size() > v2.size()) {
        v = more(v, v1, i, f);
    } else if (v1.size() < v2.size())
        v = more(v, v2, i, f);
    else {
        if (f)
            v.push_back(1);
    }


    cout << '[';
    for (auto j = v.rbegin(); j < v.rend(); ++j) {
        cout << *j;
        if(j != v.rend() - 1)
            cout << ", ";
    }
    cout << ']' << endl;


    return 0;
}
