#include <bits/stdc++.h>

#define ll long long

using namespace std;

vector<bool> ch(vector<bool> p, vector<bool> v) {
    if (!p[1])
        return v;
    vector<bool> r(3, true);
    if (!p[0]) {
        if (!v[0])
            r[0] = false;
        if (!v[1])
            r[1] = false;
    }
    if (!p[2]) {
        if (!v[2])
            r[2] = false;
        if (!v[1])
            r[1] = false;
    }

    return r;
}

int
main()
{
    ll tests;
    cin >> tests;
    for(ll test = 0; test < tests; ++test) {
        ll n, q;
        cin >> n >> q;
        vector<vector<bool>> v(n + 1, {{}, {}, {}});

        for(ll bar = 0; bar < q; ++bar) {
            ll x, y;
            cin >> x >> y;
            v[x][y - 1] = true;
        }

        const vector<bool> e(3, {});
        const vector<bool> f(3, true);
        vector<bool> p(e);
        bool fl = true;
        for (ll i = 2; i <= n; ++i) {
            if (v[i] == f) {
                cout << i - 1 << endl;
                fl = false;
                break;
            }
            if (v[i] != e) {
                if (p != e) {
                    vector<bool> c = ch(p, v[i]);
                    if (c == f) {
                        cout << i - 1 << endl;
                        fl = false;
                        break;
                    } else {
                        p = c;
                    }
                } else {
                    p = v[i];
                }
            } else {
                p = e;
            }
        }
        if (fl) {
            cout << n << endl;
        }
    }

    return 0;
}
