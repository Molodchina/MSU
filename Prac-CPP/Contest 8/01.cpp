#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using std::string, std::cin, std::cout, std::endl, std::exception;

class S
{
private:
    string _s;
public:
    S () = default;
    S (const string &s) : _s{s} {};
    S (const S &other) : _s{other._s} {}
    ~S() {
        cout << _s << endl;
    }
};

void rec () {
    string s;
    if (cin >> s) {
        S str {s};
        try {
            rec();
        } catch (const int &err) {
            throw err;
        }
    } else {
        throw 1;
    }
}

int main()
{
    try {
        rec();
    } catch (const int &err) {}
    return 0;
}