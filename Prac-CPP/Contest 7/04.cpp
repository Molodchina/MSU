#include <iostream>
#include <cmath>

using std::max, std::min, std::cout, std::endl;

// Traversal alhoritm was taken
// from https://habr.com/ru/articles/125751/

namespace Game
{
    template <typename T>
    class Coord
    {
    public:
        typedef T value_type;
        T row, col;
        Coord (T r = 0, T c = 0) : row{r}, col{c} {};
    };

    template <typename T>
    T max_abs(const T &a, const T &b) {
        T v1 = a, v2 = b;
        if (a < 0)
            v1 *= -1;
        if (b < 0)
            v2 *= -1;
        if (v1 >= v2)
            return v1;
        return v2;
    }

    template <typename T>
    T r_vec(const Coord<T> &a) {
        T res = a.row - a. col / 2;
        if (a.col % 2)
            return --res;
        return res;
    }

    template <typename T>
    T dist (const Coord<T> &size, const Coord<T> &a, const Coord<T> &b) {
        if (a.row > size.row || a.col > size.col)
            return (T) 0;
        if (b.row > size.row || b.col > size.col)
            return (T) 0;

        T r1 = r_vec(a);
        T r2 = r_vec(b);
        T max2 = max_abs(r1 - r2, a.col - b.col);

        T h1 = r1 + a.col;
        T h2 = r2 + b.col;
        return max_abs(max2, h1 - h2);
    }
}
