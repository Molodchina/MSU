#include <string>
#include <iostream>
#include <string>

using std::string, std::cin, std::cout, std::endl;

int print(const string &s) {
    size_t pos = 0;
    for (; pos < s.length() && (s[pos] == '3' || s[pos] == '4'); ++pos) {}
    for (; pos < s.length() && (s[pos] == '1' || s[pos] == '2'); ++pos) {}
    return pos == s.length();
}

int main()
{
    string s;
    while (cin >> s) {
        cout << print(s) << endl;
    }
}
