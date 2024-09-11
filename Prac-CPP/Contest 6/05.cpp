#include <iostream>
#include <vector>
#include <algorithm>

using std::cout, std::endl, std::swap, std::move;

template<class Type>
bool cmp(const Type &a, const Type &b)
{
    if (a < b)
        return true;
    return false;
}

template<class RandomIt>
auto selection_sort(RandomIt first, RandomIt last)
{
    if (first == last)
        return;

    for (auto i = first; i != last; ++i) {
        auto cur = i;
        for (auto j = cur; j != last; ++j) {
            if (cmp(*j, *cur))
                cur = j;
        }

        if (cur != i) {
            swap(*i, *cur);
        }
    }
}

template<class RandomIt, class Compare>
void selection_sort(RandomIt first, RandomIt last, Compare comp = cmp)
{
    if (first == last)
        return;

    for (auto i = first; i != last; ++i) {
        auto cur = i;
        for (auto j = cur; j != last; ++j) {
            if (comp(*j, *cur))
                cur = j;
        }

        if (cur != i) {
            swap(*i, *cur);
        }
    }
}

int main()
{
    std::vector <int> v = {5, 3, 4, 2, 1, };
    for (int &i : v)
        cout << i << ' ';
    cout << endl;

    selection_sort(v.begin(), v.end());
    for (int &i : v)
        cout << i << ' ';
    cout << endl;
}
