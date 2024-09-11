#include <cmath>
#include <string>
#include <sstream>
#include <iostream>

using std::cin, std::cout, std::endl, std::string,
        std::sqrt, std::isdigit, std::stod, std::ostringstream;;

namespace numbers
{
    class complex
    {
    public:
        complex(const double re = 0.0, const double im = 0.0) : a{re}, b{im} {}

        explicit complex(std::string s)
        {
            string re, im;
            for (auto i = s.begin() + 1; i < s.end() - 1 && *i != ','; ++i) {
                re.push_back(*i);
            }
            bool flag = false;
            for (auto i = s.begin() + 1; i < s.end() - 1 && *i != '}'; ++i) {
                if (flag) {
                    im.push_back(*i);
                } else if (*i == ',') {
                    flag = true;
                }
            }
            a = stod(re);
            b = stod(im);
        }

        double re() const{
            return a;
        }

        double im() const{
            return b;
        }

        double abs2() const{
            return a * a + b * b;
        }

        double abs() const{
            return sqrt(abs2());
        }

        string to_string() const {
            ostringstream a_out, b_out;
            a_out.precision(10);
            b_out.precision(10);

            a_out << a;
            b_out << b;

            string s = "(" + a_out.str() + "," + b_out.str() + ")";
            return s;
        }
        const complex  &operator+= (const complex &other) {
            a += other.re();
            b += other.im();
            return *this;
        }
        const complex &operator-= (const complex &other) {
            a -= other.re();
            b -= other.im();
            return *this;
        }
        const complex &operator*= (const complex &other) {
            double tmp_re = a * other.re() - b * other.im();
            double tmp_im = b * other.re() + a * other.im();
            a = tmp_re;
            b = tmp_im;
            return *this;
        }
        const complex &operator/= (const complex &other) {
            a = (a * other.re() + b * other.im())
                            / other.abs2();
            b = (b * other.re() - a * other.im())
                            / other.abs2();
            return *this;
        }
        friend complex operator~ (const complex &other) {
            return complex(other.re(), -other.im());
        }
        friend complex operator- (const complex &other) {
            return complex(-other.re(), -other.im());
        }
    private:
        double a, b;
    };
    complex operator+ (const complex &a, const complex &b) {
        complex res(a.re(), a.im());
        return res += b;
    }
    complex operator- (const complex &a, const complex &b) {
        complex res(a.re(), a.im());
        return res -= b;
    }
    complex operator* (const complex &a, const complex &b) {
        complex res(a.re(), a.im());
        return res *= b;
    }
    complex operator/ (const complex &a, const complex &b) {
        complex res(a.re(), a.im());
        return res /= b;
    }
};
