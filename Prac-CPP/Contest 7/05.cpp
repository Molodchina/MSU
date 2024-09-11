#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <cassert>

class Figure
{
public:
    virtual bool equals (Figure *other) const = 0;
    virtual ~Figure() {};
};

using std::string, std::stod, std::cout, std::endl;

class Rectangle: public Figure
{
public:
    Rectangle(int a = 0, int b = 0): _a{a}, _b{b} {}

    bool equals (Figure *other) const {
        return true;
    }

private:
    int _a, _b;
};

class Triangle: public Figure
{
public:
    Triangle(int a = 0, int b = 0, int c = 0): _a{a}, _b{b}, _c{c} {}

    bool equals (Figure *other) const {
        return true;
    }

private:
    int _a, _b, _c;
};

int main()
{
    Rectangle r1(10, 5), r2(10, 2), r3(10, 5), r4(5, 10);
    Triangle t1(1, 2, 3);
    Figure *f = &r1;

    assert(!f->equals(&r2));
    assert(f->equals(&r3));
    assert(!f->equals(&r4));
    assert(!f->equals(&t1));
    assert(!f->equals(nullptr));
}
