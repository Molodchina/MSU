#include <iostream>
#include <string>
#include <stack>

//alg from https://www.geeksforgeeks.org/postfix-to-infix/

using std::cin, std::cout, std::endl, std::string, std::stack;

bool o_ch(char c)
{
    return c == '+' || c == '-'
           || c == '*' || c == '/';
}


string get_r(const string& s)
{
    stack<string> st;

    for (char i: s)
    {
        if (i == ' ')
            continue;
        if (o_ch(i)) {
            string op1 = st.top();
            st.pop();
            string op2 = st.top();
            st.pop();
            st.push(string ("(" + op2 +
                            i + op1 + ")"));
        } else {
            st.emplace(1,i);
        }
    }

    return st.top();
}

int main()
{
    string s;
    cin >> s;
    cout << get_r(s) << endl;
}
