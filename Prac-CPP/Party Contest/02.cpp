#include <bits/stdc++.h>

using namespace std;

int main()
{
    long x, m, b, e;
    cin >> x >> m;
    {
        long s_h{}, s_m{}, e_h{}, e_m{};
        char c;
        cin >> s_h >> c >> s_m >> c >> e_h >> c >> e_m;
        b = min(s_h * 60 + s_m, e_h * 60 + e_m);
        e = max(e_h * 60 + e_m, s_h * 60 + s_m);
    }

    vector<pair<long, long>> w;
    for (long pos = 0; pos < m; ++pos) {
        long s_h{}, s_m{}, e_h{}, e_m{}, s{}, l{};
        int a;
        char c;
        cin >> a >> s_h >> c >> s_m >> c >> e_h >> c >> e_m;
        s = min(s_h * 60 + s_m, e_h * 60 + e_m);
        l = max(e_h * 60 + e_m, s_h * 60 + s_m);
        w.emplace_back(s, l);
    }
    if (w.empty()) {
        printf("%02ld:%02ld-%02ld:%02ld\n", b / 60, b % 60,
               e / 60, e % 60);
        return 0;
    }
    sort(w.begin(), w.end());

    vector<pair<long, long>> r;
    {
        size_t i{};
        for (; i < w.size() && w[i].second < b; ++i) {}
        if (i == w.size()) {
            printf("%02ld:%02ld-%02ld:%02ld\n", b / 60, b % 60,
                   e / 60, e % 60);
            return 0;
        }
        auto prev = w[i++];
        for(; i < w.size(); ++i) {
            if (w[i].first >= e)
                break;
            if (prev.second >= w[i].first) {
                long s = prev.first, l = max(prev.second, w[i].second);
                if (s < b)
                    s = b;
                if (l > e)
                    l = e;
                prev = pair(s, l);
            } else {
                r.push_back(prev);
                prev = w[i];
            }
        }
        if (prev.second > e)
            prev.second = e;
        if (prev.first < b)
            prev.first = b;
        if (prev.first <= e && prev.second >= b)
            r.push_back(prev);
        w.clear();
    }

    pair<long, pair<long, long>> res{};
    for(auto & i : r) {
        if (i.first > b) {
            if (i.first - b > res.first) {
                res = pair(i.first - b, pair(b, i.first));
            }
        } else if (i.second == e) {
            cout << "ALARM\n";
            return 0;
        }
        b = i.second;
    }
    if (e - b > res.first)
        res = pair(e - b, pair(b, e));
    if (!res.first) {
        cout << "ALARM\n";
        return 0;
    }
    printf("%02ld:%02ld-%02ld:%02ld\n", res.second.first/60, res.second.first%60,
           res.second.second/60, res.second.second%60);
    return 0;
}
