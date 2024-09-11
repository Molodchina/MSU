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
  string res;
  if ((s1.back() == '*' || s1.back() == '|' || s1.size() <= 1) && oper.compare("*"))
    res = s1;
  else if (s1.size() <= 1)
    res = s1;
  else
    res = "(" + s1 + ")";

  if ((string {res.back()}).compare(oper) && !s1.empty()) 
    res += oper;

  if (s2[0] == '(' || s2.size() <= 1)
    return res + s2;
  return res + "(" + s2 + ")";
}


size_t states_len;
string connect(DFA &d, vector<vector<string>> trans) {
  int init = stoi(d.get_initial_state());
  set<string> finals_set = d.get_final_states();
  int final = states_len - 1;

  string self_trans_init;
  if (!trans[init][init].empty()) {
    self_trans_init = "(" + trans[init][init] + ")*";
  }

  // string self_trans_final;
  // if (!trans[final][final].empty())
  //   self_trans_final = concat(trans[final][final], "", "*");

  // string res;
  // string right = concat(trans[init][final], self_trans_final);
  // if (d.is_final(to_string(init))) {
  //   if (!trans[final][init].empty()) {
  //     // if (!self_trans_init.empty())
  //     //   res = self_trans_init + "(|" + right + "(|" + concat(trans[final][init], self_trans_init) + "))*";
  //     // else
  //     //   res = "(" + right + "(|" + trans[final][init] + "))*";

  //     res = "(" + concat(self_trans_init, concat(right, trans[final][init]), "|") + ")*" + "(" + concat(self_trans_init, right, "|") + ")";
    
  //   } else {
  //     if (!self_trans_init.empty())
  //       res = concat(self_trans_init, right, "|");
  //     else
  //       res = "|" + right;
  //   }

  // } else {
  //   if (!trans[final][init].empty()) {
  //     if (!self_trans_init.empty())
  //       res = "(" + concat(self_trans_init, concat(right, trans[final][init]), "|") + ")*" + right;
  //     else
  //       res = concat(concat(right, trans[final][init]), "", "*") + right;
  //   } else {
  //     if (!self_trans_init.empty())
  //       res = concat(self_trans_init, right);
  //     else
  //       res = right;
  //   }
  // }

  string res;
  res = concat(self_trans_init, trans[init][final]);

  return res;
}


int get_middle(DFA &d) {
  set<string> finals_set = d.get_final_states();
  set<string> states = d.get_states();
  string init_state = d.get_initial_state();

  for (auto it = states.begin(); it != states.end(); ++it) {
    auto find_it = find(finals_set.begin(), finals_set.end(), *it);
    if (find_it == finals_set.end() && (*it).compare(init_state)) {
      return stoi(*it);
    }
  }

  return -1;
}


bool stop = true;
pair<DFA, vector<vector<string>>> del_middle(DFA &d, vector<vector<string>> trans) {
  int middle = get_middle(d);
  if (middle == -1) {
    stop = false;
    return {d, trans};
  }

  string self_trans;
  map<size_t, string> mid_trans;
  for (size_t i = 0; i < states_len; ++i) {
    string cur_trans;
    if (trans[i][middle].empty())
      continue;

    cur_trans = trans[i][middle];
    if (i == middle) {
      self_trans = concat(cur_trans, "", "*");
      trans[i][middle].clear();
      continue;
    }
    
    mid_trans[i] = cur_trans;
    trans[i][middle].clear();
  }

  cout << "TRANS TO MID: " << endl;
  for (auto const& [key, mid_tran] : mid_trans)
    cout << '\t' << key << ": " << mid_tran << endl;

  for (size_t i = 0; i < states_len; ++i) {
    if (trans[middle][i].empty() || i == middle)
      continue;

    for (auto const& [key, mid_tran]: mid_trans) {
      string cur_trans;
      if (!trans[key][i].empty())
        cur_trans = trans[key][i] + "|";
        trans[key][i] = cur_trans + concat(concat(mid_tran, self_trans), trans[middle][i]);
    }
    trans[middle][i].clear();
  }

  DFA new_d(d);
  new_d.delete_state(to_string(middle));
  return {new_d, trans};
}


int get_final(DFA &d) {
  set<string> finals_set = d.get_final_states();
  string init = d.get_initial_state();
  vector<string> finals{finals_set.begin(), finals_set.end()};

  if ((finals.size() == 2 && d.is_final(init)) || ((finals.size() == 1 && !d.is_final(init))))
    return -1;

  for (size_t i = 0; i < finals.size() - 1; ++i)
    if (init.compare(finals[i]))
      return stoi(finals[i]);

  return -1;
}


pair<DFA, vector<vector<string>>> del_final(DFA &d, vector<vector<string>> trans) {
  int final = get_final(d);
  if (final == -1) {
    stop = false;
    return {d, trans};
  }

  string self_trans;
  map<size_t, string> final_trans;
  for (size_t i = 0; i < states_len; ++i) {
    string cur_trans;
    if (trans[i][final].empty())
      continue;

    cur_trans = trans[i][final];
    if (i == final) {
      self_trans = concat(cur_trans, "", "*");
      trans[i][final].clear();
      continue;
    }
    
    final_trans[i] = cur_trans;
    trans[i][final].clear();
  }

  cout << "TRANS TO FINAL " << final << ":" << endl;
  for (auto const& [key, fin_tran] : final_trans)
    cout << '\t' << key << ": " << fin_tran << endl;

  bool new_final_checked = false;
  for (size_t i = 0; i < states_len - 1; ++i) {
    for (auto const& [key, fin_tran]: final_trans) {
      if (!new_final_checked) {
        string right = concat(concat(fin_tran, self_trans), trans[final][states_len - 1]);
        if (d.is_final(to_string(key)))
          trans[key][states_len - 1] += "|" + right;
        else
          trans[key][states_len - 1] = concat(trans[key][states_len - 1], right, "|");
      }

      if (trans[final][i].empty() || i == final)
        continue;
      string cur_trans;
      if (!trans[key][i].empty())
        cur_trans = concat(cur_trans, trans[key][i], "|");
      cout << "ZERO_TRANS[" << key << "][" << i << "]:\t" << cur_trans << endl;

      trans[key][i] = concat(cur_trans, concat(concat(fin_tran, self_trans), trans[final][i]), "|");
      cout << "FINAL_TRANS[" << key << "][" << i << "]:\t" << trans[key][i] << endl << endl;

      cout << "TRANS TO NEW[" << key << "][" << states_len - 1 << "]:\t" << trans[key][states_len - 1] << endl << endl;
    }
    new_final_checked = true;
    trans[final][i].clear();
  }
  trans[final][states_len - 1].clear();

  DFA new_d(d);
  new_d.delete_state(to_string(final));
  return {new_d, trans};
}


string minimize(string s) {
  return s;
}


string dfa2re(DFA &d) {
  DFA new_d(d);
  states_len = d.size() + 3;
  vector<vector<string>> trans(states_len, vector<string> (states_len));
  string alphas = d.get_alphabet().to_string();

  stack<string> achieved;
  vector<bool> was_checked(states_len);
  was_checked[stoi(new_d.get_initial_state())] = true;
  achieved.push(new_d.get_initial_state());
  while (!achieved.empty()) {
    string state = achieved.top();
    achieved.pop();

    for (char alpha: alphas) {
      if (new_d.has_trans(state, alpha)) {
        string last_state = new_d.get_trans(state, alpha);
        if (trans[stoi(state)][stoi(last_state)].empty())
          trans[stoi(state)][stoi(last_state)] = string {alpha};
        else
          trans[stoi(state)][stoi(last_state)] += "|" + string {alpha};

        if (!was_checked[stoi(last_state)]) {
          achieved.push(last_state);
          was_checked[stoi(last_state)] = true;
        }
      }
    }
  }

  cout << "INIT TRANS:" << endl;
  for (size_t i = 0; i < states_len; ++i) {
    cout << i << ":" << endl;
    for (size_t j = 0; j < states_len; ++j)
      cout << "\t" << j << ": " << trans[i][j] << endl;
  }

  // While middle states > 0
  stop = get_middle(new_d) != -1;
  while (stop) {
    tie(new_d, trans) = del_middle(new_d, trans);

    cout << "CUR MIDDLE TRANS:" << endl;
    for (size_t i = 0; i < states_len; ++i) {
      cout << i << ":" << endl;
      for (size_t j = 0; j < states_len; ++j)
        cout << "\t" << j << ": " << trans[i][j] << endl;
    }
  }

  // While end states >= 1
  int max_state = states_len - 1;
  new_d.create_state(to_string(max_state), true);

  stop = get_final(new_d) != -1;
  while (stop) {
    tie(new_d, trans) = del_final(new_d, trans);

    cout << "CUR FINAL  TRANS:" << endl;
    for (size_t i = 0; i < states_len; ++i) {
      cout << i << ":" << endl;
      for (size_t j = 0; j < states_len; ++j)
        cout << "\t" << j << ": " << trans[i][j] << endl;
    }
  }

  // Connect start and connected finals
  string res = connect(new_d, trans);
  // cout << "HERE" << endl;

  // minimize
  return minimize(res);
}
