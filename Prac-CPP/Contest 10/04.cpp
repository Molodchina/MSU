#include <iostream>
#include <string>
#include <stack>
#include <map>

// alg from https://prepinsta.com/cpp-program/infix-to-postfix-conversion-using-stack/

using std::cin, std::cout, std::endl, std::string, std::stack, std::pair, std::map;

bool o_ch(char c)
{
    return c == '+' || c == '-'
           || c == '*' || c == '/' || c == '&'
           || c == '^' || c == '|';
}

int priority (char alpha){
    if (alpha == '|')
        return 1;
    if (alpha == '^')
        return 2;
    if (alpha == '&')
        return 3;
    if (alpha == '+' || alpha =='-')
        return 4;
    if (alpha == '*' || alpha =='/')
        return 5;
    return 6;
}

string get_r(const string& s)
{
    stack<pair<string, int>> st;

    for (char i: s) {
        if (o_ch(i)) {
            auto [op1, idx1] = st.top();
            st.pop();
            auto [op2, idx2] = st.top();
            st.pop();

            int prio = priority(i);
            if (idx1 > prio && idx2 >= prio)
                st.emplace(string (op2 + i + op1), prio);
            else if (idx1 <= prio && idx2 < prio)
                st.emplace(string ("(" + op2 + ")" + i + "(" + op1 + ")"), prio);
            else if (idx2 < prio)
                st.emplace(string ("(" + op2 + ")" + i + op1), prio);
            else
                st.emplace(string (op2 + i + "(" + op1 + ")"), prio);
        } else {
            st.emplace(string (1, i), priority(i));
        }
    }

    return st.top().first;
}

string convert(string infix)
{
    int i = 0;
    string postfix;
    stack <int> s;

    while(infix[i]!='\0') {
        if (infix[i] == ' ') {
            ++i;
        } else if(infix[i] >= 'a' && infix[i] <= 'z') {
            postfix += infix[i++];
        } else if(infix[i] == '(') {
            s.push(infix[i++]);
        } else if(infix[i] == ')') {
            while(s.top() != '('){
                postfix += s.top();
                s.pop();
            }
            s.pop();
            ++i;
        } else {
            while (!s.empty() && priority(infix[i]) <= priority(s.top())) {
                postfix += s.top();
                s.pop();
            }
            s.push(infix[i]);
            ++i;
        }
    }
    while(!s.empty()) {
        postfix += s.top();
        s.pop();
    }

    return get_r(postfix);
}

int main()
{
    string s;
    getline(cin, s);
    cout << convert(s) << endl;

    return 0;
}