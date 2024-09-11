#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <list>

using std::cin, std::cout, std::endl;

int main()
{
    std::list<long> m;
    long val;

    while (cin >> val && val != 0) {
        m.push_back(val);
    }

    long cmd_val;
    while (cin >> val) {
        if (val < 0 && (-val - 1 < (long) m.size())) {
            auto elem = m.begin();
            std::advance(elem, -val - 1);
            m.erase(elem);
        } else if (val > 0) {
            cin >> cmd_val;

            if (val - 1 > (long) m.size()) {
                m.push_back(cmd_val);
                continue;
            } else {
                auto elem = m.begin();
                std::advance(elem, val - 1);
                m.insert(elem, cmd_val);
            }
        }
    }

    for (auto i: m)
        cout << i << endl;
    m.clear();
    return 0;
}
