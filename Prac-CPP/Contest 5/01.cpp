#include <iostream>
#include <vector>
#include <algorithm>

using std::cin, std::cout, std::endl;

unsigned int countSetBits(unsigned int n)
{
    unsigned int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

bool cmp(const unsigned int &a, const unsigned int &b)
{
    unsigned int v1 = countSetBits(a), v2 = countSetBits(b);
    if (v1 < v2)
        return true;
    return false;
}

int main()
{
    std::vector<unsigned int> v;
    int tmp;
    while (cin >> tmp) {
        v.push_back(tmp);
    }
    std::stable_sort(v.begin(), v.end(), cmp);
    for (auto i: v) {
        cout << i << endl;
    }
}