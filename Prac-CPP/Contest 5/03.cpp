#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <list>

using std::cin, std::cout, std::endl, std::string, std::map, std::list,
        std::vector, std::pair, std::setw, std::setfill, std::stoi, std::unique;


class Date
{
public:
    int _y, _d, _m;
    Date(const string &s) {
        string y, d, m;
        auto i = s.begin();
        for (; i < s.end() && *i != '/'; ++i) {
            y.push_back(*i);
        }
        ++i;
        for (; i < s.end() && *i != '/'; ++i) {
            m.push_back(*i);
        }
        ++i;
        for (; i < s.end(); ++i) {
            d.push_back(*i);
        }
        _y = stoi(y);
        _m = stoi(m);
        _d = stoi(d);
    }

    string out() const {
        std::stringstream s;
        s << std::setw(2) << std::setfill('0') << _y << '/';
        s << std::setw(2) << std::setfill('0') << _m << '/';
        s << std::setw(2) << std::setfill('0') << _d ;
        return s.str();
    }
};

bool operator > (const Date &a, const Date &b) {
    if (a._y < b._y)
        return false;
    else if (a._y == b._y) {
        if (a._m < b._m)
            return false;
        else if (a._m == b._m)
            if (a._d <= b._d)
                return false;
    }
    return true;
}

bool operator < (const Date &a, const Date &b) {
    if (a._y < b._y)
        return true;
    else if (a._y > b._y)
        return false;
    if (a._m < b._m)
        return true;
    else if (a._m > b._m)
        return false;
    if (a._d < b._d)
        return true;
    return false;
}

bool operator >= (const Date &a, const Date &b) {
    if (a._y < b._y)
        return false;
    if (a._m < b._m)
        return false;
    if (a._d < b._d)
        return false;
    return true;
}

bool operator <= (const Date &a, const Date &b) {
    if (a._y > b._y)
        return false;
    if (a._m > b._m)
        return false;
    if (a._d > b._d)
        return false;
    return true;
}

bool operator != (const Date &a, const Date &b) {
    if (a._y != b._y && a._m != b._m && a._d != b._d)
        return true;
    return false;
}

bool operator == (const Date &a, const Date &b) {
    if (a._y == b._y && a._m == b._m && a._d == b._d)
        return true;
    return false;
}

int main()
{
    map<std::string, map<Date, int>> m{};
    list<Date> ds;
    string tmp_n, tmp_d;
    int tmp_g;
    int max_n_len = 0;
    while(cin >> tmp_n >> tmp_d >> tmp_g) {
        Date d(tmp_d);
        m[tmp_n][d] = tmp_g;
        ds.push_back(d);
        if (max_n_len < (int) tmp_n.size())
            max_n_len = (int) tmp_n.size();
    }
    ds.sort();
    ds.unique();
    max_n_len += 2;
    cout << std::setiosflags(std::ios::left);
    cout << setw(max_n_len) << '.' ;
    for (auto i: ds) {
        cout << setw(15) << i.out();
    }
    cout << endl;

    for (auto i: m) {
        cout << setw(max_n_len) << i.first;

        for (auto d: ds) {
            if (i.second.contains(d))
                cout << setw(15) << i.second[d];
            else
                cout << setw(15) << '.';
        }
        cout << endl;
    }

    return 0;
}