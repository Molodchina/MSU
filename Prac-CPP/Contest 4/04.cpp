#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using std::cin, std::cout, std::endl, std::distance,
        std::setprecision, std::fixed, std::for_each;

class Avg
{
public:
    Avg(): res(0.0), len(0) {}
    void operator() (double val) {
        res += val;
        ++len;
    }
    double print() {
        return res / len;
    }
private:
    double res;
    long len;
};

int main()
{
    std::vector<double> v;
    double val;

    while(cin >> val) {
        v.push_back(val);
    }

    size_t len = v.size();

    long percent = 10;
    long diff = (long) len / percent;
    auto start = v.begin() + diff;
    auto end = v.end() - diff;
    diff = distance(start, end) / percent;
    std::sort(start, end);
    start += diff;
    end -= diff;

    Avg res = for_each(start, end, Avg());
    cout << fixed << setprecision(10)
         << res.print() << endl;
}
