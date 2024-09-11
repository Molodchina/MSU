#include "api.hpp"
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstdlib>
#include <stack>
#include <cassert>
#include <utility>
#include <map>

using namespace std;


string concat(string s1, string s2, string oper = "") {
  if (s1.empty() && s2.empty())
    return "";

  string res;
  if (s1.back() == ')' || s1.back() == '*' || s1.size() <= 1)
    res = s1;
  else
    res = "(" + s1 + ")";
  res += oper;
  if (s2[0] == '(' || s2.size() <= 1)
    return res + s2;
  
  return res + "(" + s2 + ")";
}


size_t find_end_parenth(const string &s, size_t pos) {
  int count = 1;
  for (size_t i = pos + 1; i < s.length(); ++i) {
    char c = s[i];
    switch(c) {
    case '(':
      ++count;
      break;
    case ')':
      --count;
      if (!count)
        return i;
      break;
    default:
      break;
    }
  }
  return std::string::npos;
}


size_t states_amount;
string minimize(string s) {
  // for (size_t i = 0; i < s.size(); ++i) {
  //   char c = s[i];

  //   switch (c) {
  //   case '(':
  //     cur_pos = find_end_parenth(s, pos);
      
  //     break;
  //   case '|':
  //     break;
  //   case '*':
  //     break;
  //   default:
  //     break;
  //   }
  // }

  return s;
}


string dfa2re(DFA &d) {
  DFA new_d(d);
  states_amount = d.size();
  string alphas = d.get_alphabet().to_string();
  int init_state = stoi(new_d.get_initial_state());

  vector<vector<string>> r(states_amount, vector<string> (states_amount, ""));
  int power = 0;

  // init r
  stack<string> achieved;
  vector<bool> was_checked(states_amount);

  was_checked[init_state] = true;
  achieved.push(to_string(init_state));
  while (!achieved.empty()) {
    string state = achieved.top();
    achieved.pop();
    bool self_fl = false;

    for (char alpha: alphas) {
      if (new_d.has_trans(state, alpha)) {
        string last_state = new_d.get_trans(state, alpha);
        if (r[stoi(state)][stoi(last_state)].empty())
          r[stoi(state)][stoi(last_state)] = string {alpha};
        else
          r[stoi(state)][stoi(last_state)] += "|" + string {alpha};

        if (!state.compare(last_state))
          self_fl = true;

        if (!was_checked[stoi(last_state)]) {
          achieved.push(last_state);
          was_checked[stoi(last_state)] = true;
        }
      }
    }
    if (self_fl)
      r[stoi(state)][stoi(state)] += "|_";
  }

  cout << "R " << power + 1 << endl;
  for (size_t i = 0; i < states_amount; ++i) {
    cout << i << ":" << endl;
    for (size_t j = 0; j < states_amount; ++j)
      cout << "\t" << j << ": " << r[i][j] << endl;
  }

  while (power < states_amount) {
    vector<vector<string>> cur_r(states_amount, vector<string> (states_amount, ""));

    for (size_t i = 0; i < states_amount; ++i) {
      for (size_t j = 0; j < states_amount; ++j) {
        if (r[i][j].empty()) {
          if (r[i][power].empty() || r[power][j].empty())
            continue;
          cur_r[i][j] = minimize(concat(r[i][power], concat(concat(r[power][power], "", "*"), r[power][j])));
        } else if (r[i][power].empty() || r[power][j].empty()) {
            if (r[i][j].empty())
              continue;
            cur_r[i][j] = r[i][j];
        }
        else {
          string right = concat(r[i][power], concat(concat(r[power][power], "", "*"), r[power][j]));
          cur_r[i][j] = minimize(concat(r[i][j], right, "|"));
        }
      }
    }

    cout << "R " << power + 1 << endl;
    for (size_t i = 0; i < states_amount; ++i) {
      cout << i << ":" << endl;
      for (size_t j = 0; j < states_amount; ++j)
        cout << "\t" << j << ": " << cur_r[i][j] << endl;
    }
    r = cur_r;
    ++power;
  }

  string res;
  for (size_t i = 0; i < states_amount; ++i) {
    if ((i != init_state) && (!r[init_state][i].empty())) {
      if (!res.empty())
        res += "|";
      res += r[init_state][i];
    }
  }

  // minimize
  return res;
}
