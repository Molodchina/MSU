#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>
#include <cstdint>
#include <chrono>
#include <cmath>
#include <cstdlib>

using std::string, std::cin, std::cout, std::endl, std::stoul,
        std::chrono::year_month_day, std::abs;


int main()
{
    using namespace std::chrono;
    year_month_day prev{};
    long long res = 0;
    bool f = false;
    string s;

    while (cin >> s) {
        string tmp;
        unsigned int date[3] {};
        int pos = 0;
        for (auto i = s.begin(); ; ++i) {
            if (*i == '-' || i == s.end()) {
                date[pos++] = stoul(tmp);
                tmp.clear();
                if (i == s.end())
                    break;
            } else {
                tmp.push_back(*i);
            }
        }
        year_month_day cur{year{(int) date[0]}, month{date[1]}, day{date[2]}};
//        cout << static_cast<int>(cur.year()) << '-' << static_cast<unsigned>(cur.month())
//            << '-' << static_cast<unsigned>(cur.day()) << endl;
        if (!f)
            prev = cur;
        if (f) {
            res += abs((sys_days{cur} - sys_days{prev}).count());
            prev = cur;
        }
        f = true;
    }
    cout << res << endl;
}
