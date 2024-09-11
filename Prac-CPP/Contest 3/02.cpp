#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include <new>
#include "01.cpp"

using std::cin, std::cout, std::endl;

namespace numbers
{
    class complex_stack
    {
    public:
        complex_stack() : mas(nullptr), len(0) {}

        complex_stack(const complex_stack &other, const size_t extra = 0)
        {
            len = other.size() + extra;
            mas = new complex[len];
            for (size_t i = 0; i < other.size(); ++i) {
                mas[i] = other.mas[i];
            }
        }

        ~complex_stack()
        {
            len = 0;
            delete[] mas;
        }

        size_t size() const
        {
            return len;
        }

        complex operator[] (const size_t idx) const {
            return mas[idx];
        }

        complex_stack operator<< (const complex val) const {
            complex_stack res(*this, 1);
            res.mas[res.size() - 1] = val;
            return res;
        }

        complex_stack operator~ () const {
            complex_stack res(*this);
            --res.len;
            return res;
        }

        complex operator+ () const {
            return mas[size() - 1];
        }

        complex_stack &operator= (const complex_stack &other) {
            if (this == &other) {
                return *this;
            }

            delete [] mas;
            len = other.size();
            mas = new complex[len];

            for (size_t i = 0; i < other.size(); ++i) {
                mas[i] = other.mas[i];
            }
            return *this;
        }
    private:
        complex *mas;
        size_t len;
    };
};
