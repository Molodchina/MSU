#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include "01.cpp"

using std::string, std::stod, std::cout, std::endl;

class Rectangle : public Figure
{
public:
    static Rectangle *make (const string &s) {
        std::istringstream strin(s);
        double an, bn;
        strin >> an >> bn;
        Rectangle *rec = new Rectangle;
        rec->_x = an;
        rec->_y = bn;
        return rec;
    }
    double get_square() const {
        return _x * _y;
    }
    string to_string() const {
        string s = std::to_string(_x) + ' ' + std::to_string(_y);
        return s;
    }
private:
    double _x, _y;
};

class Square : public Figure
{
public:
    static Square *make (const string &s) {
        auto tmp = new Square;
        string c;
        for (auto i : s) {
            c.push_back(i);
        }
        tmp->_c = stod(c);
        return tmp;
    }
    double get_square() const {
        return _c * _c;
    }
    string to_string() const {
        return std::to_string(_c);
    }
private:
    double _c;
};

class Circle : public Figure
{
public:
    static Circle *make (const string &s) {
        auto tmp = new Circle;
        string r;
        for (auto i : s) {
            r.push_back(i);
        }
        tmp->_r = stod(r);
        return tmp;
    }
    double get_square() const {
        return M_PI * _r * _r;
    }
    string to_string() const {
        return std::to_string(_r);
    }
private:
    double _r;
};
