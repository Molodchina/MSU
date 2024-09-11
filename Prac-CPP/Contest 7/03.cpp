#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <map>
#include <functional>
#include <sstream>
//#include "02.cpp"

using std::string, std::stod, std::cout, std::endl, std::cin,
        std::vector, std::unique_ptr, std::map, std::function,
        std::stringstream, std::getline;


class F
{
private:
    F() {};
public:
    static F &factory_instance() {
        static F f;
        return f;
    }

    unique_ptr<Figure> create_figure(const string &s) {
        map<char, function<unique_ptr<Figure> (const string&)>> m
                {
                        {
                                'R', [](const string &str)
                                     {
                                         return unique_ptr<Rectangle>(Rectangle::make(str));
                                     }
                        },
                        {
                                'C', [](const string &str)
                                     {
                                         return unique_ptr<Circle>(Circle::make(str));
                                     }
                        },
                        {
                                'S', [](const string &str)
                                     {
                                         return unique_ptr<Square>(Square::make(str));
                                     }
                        }
                };
        char t;
        string p;
        stringstream stream(s);
        stream >> t;

        getline(stream, p);

        return m[t](p);
    }
};


bool operator < (const unique_ptr<Figure> &v1, const unique_ptr<Figure> &v2)
{
    return v1->get_square() < v2->get_square();
}

int main() {
    vector<unique_ptr<Figure>> v;
    F f = F::factory_instance();

    string s;
    while (getline(cin, s)) {
        v.push_back(f.create_figure(s));
    }

    std::stable_sort(v.begin(), v.end());
    for (auto &i: v) {
        cout << i->to_string() << endl;
    }
    return 0;
}
