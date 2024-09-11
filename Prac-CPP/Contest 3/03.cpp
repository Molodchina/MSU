#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include "02.cpp"

using std::cin, std::cout, std::endl, numbers::complex,
        numbers::complex_stack, std::map, std::function;


namespace numbers
{
    complex
    eval(const std::vector<std::string> &args, const complex &z)
    {
        complex_stack st;

        map<char, std::function<complex_stack
                (complex_stack&)>> m
                {
                        {
                                '+', [](complex_stack &st)
                                     {
                                         complex sum;
                                         sum = +st;
                                         st = ~st;
                                         sum += +st;
                                         st = ~st;
                                         return st<<sum;
                                     }
                        },
                        {
                                '-', [](complex_stack &st)
                                     {
                                         complex min, tmp;
                                         tmp = +st;
                                         st = ~st;
                                         min = +st;
                                         st = ~st;
                                         min -= tmp;
                                         return st<<min;
                                     }
                        },
                        {
                                '*', [](complex_stack &st)
                                     {
                                         complex mul;
                                         mul = +st;
                                         st = ~st;
                                         mul *= +st;
                                         st = ~st;
                                         return st<<mul;
                                     }
                        },
                        {
                                '/', [](complex_stack &st)
                                     {
                                         complex div, tmp;
                                         tmp = +st;
                                         st = ~st;
                                         div = +st;
                                         st = ~st;
                                         div /= tmp;
                                         return st<<div;
                                     }
                        },
                        {
                                '!', [](complex_stack &st)
                                     {
                                         return st<<(+st);
                                     }
                        },
                        {
                                ';', [](complex_stack &st)
                                     {
                                         return ~st;
                                     }
                        },
                        {
                                '~', [](complex_stack &st)
                                     {
                                         complex val;
                                         val = +st;
                                         st = ~st;
                                         return st<<(~val);
                                     }
                        },
                        {
                                '#', [](complex_stack &st)
                                     {
                                         complex val;
                                         val = +st;
                                         st = ~st;
                                         return st<<(-val);
                                     }
                        }
                };

        for (auto i: args) {
            if (i[0] == '(') {
                complex val(i);
                st = st<<val;
            } else if (i[0] == 'z') {
                st = st<<z;
            } else {
                st = m[i[0]](st);
            }
        }
        return +st;
    }
}
