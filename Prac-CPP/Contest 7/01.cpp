#include <iostream>
#include <cmath>
#include <string>

class Figure
{
public:
    virtual double get_square() const = 0;
    virtual std::string to_string() const = 0;
    virtual ~Figure() {};
};
