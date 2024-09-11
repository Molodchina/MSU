#include <iostream>

using std::cin, std::cout, std::endl;

struct A{
    int val;
    bool temp = false;
    A() {
        cin >> val;
    }
    A(A& a) {
        cin >> val;
        val = a.val + val;
        temp = true;
    }
    ~A(){
        if (temp) {
            cout << val << endl;
        }
    }
};
