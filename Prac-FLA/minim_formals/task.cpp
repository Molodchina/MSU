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

using namespace std;


vector<vector<int>> final_trans;


DFA del_states(DFA &d, string alphas) {
    DFA new_d(d);
    string init_state = d.get_initial_state();
    stack<int> achieved;
    vector<vector<int>> ach_by(d.size());

    achieved.emplace(stoi(init_state));
    while (!achieved.empty()) {
      int state = achieved.top();
      achieved.pop();

      vector<int> cur_trans = final_trans[state];
      assert(alphas.size() == cur_trans.size());

      for (size_t i = 0; i < cur_trans.size(); ++i) {
          new_d.set_trans(to_string(state), alphas[i], to_string(cur_trans[i]));
          if (ach_by[cur_trans[i]].empty())
            achieved.push(cur_trans[i]);
          ach_by[cur_trans[i]].push_back(state);
      }
    }

    for (size_t i = 0; i < new_d.size(); ++i) {
      if (ach_by[i].empty() && to_string(i).compare(init_state))
        new_d.delete_state(to_string(i));
    }

    stack<int> finalized;
    vector<bool> is_fin(d.size());

    set<string> finals_set = new_d.get_final_states();
    vector<string> finals{finals_set.begin(), finals_set.end()};
    for (string state: finals) {
      finalized.push(stoi(state));
      is_fin[stoi(state)] = true;
    }

    while (!finalized.empty()) {
      int state = finalized.top();
      finalized.pop();
      for (int ach_by_state: ach_by[state]) {
          // cout << ach_by_state << ", ";
          if (!is_fin[ach_by_state])
            finalized.push(ach_by_state);
          is_fin[ach_by_state] = true;
      }
    }

    for (size_t i = 0; i < is_fin.size(); ++i) {
      if (!is_fin[i])
        new_d.delete_state(to_string(i));
    }

    return new_d;
}


vector<vector<string>> translate(vector<vector<string>> p, vector<string> cur_p, vector<vector<string>> trans) {
    vector<vector<int>> t;
    for (size_t i = 0; i < trans.size(); ++i) {
        vector<int> cur_t;

        for (string state: trans[i]) {
            for (size_t j = 0; j < p.size(); ++j) {
                auto find_it = find(p[j].begin(), p[j].end(), state);
                if (find_it != p[j].end()) {
                    // cout << "; FOUND IN GROUP: " << j << endl;
                    cur_t.push_back(j);
                    break;
                }
            }
        }

        t.push_back(cur_t);
    }

    assert(cur_p.size() == t.size());

    vector<vector<string>> res;
    vector<vector<int>> res_trans;

    for (size_t i = 0; i < cur_p.size(); ++i) {
        if (res.empty()) {
            res.push_back(vector<string> {cur_p[i]});
            res_trans.push_back(t[i]);
            continue;
        }

        auto it = find(res_trans.begin(), res_trans.end(), t[i]);
        if (it == res_trans.end()) {
            res.push_back(vector<string> {cur_p[i]});
            res_trans.push_back(t[i]);
        } else {
            size_t index = distance(res_trans.begin(), it);
            assert(index < res.size());
            res[index].push_back(cur_p[i]);
        }
    }

    for (size_t i = 0; i < res.size(); ++i) {
        final_trans.push_back(res_trans[i]);
    }
    return res;
}


DFA dfa_minim(DFA &d) {
  vector<vector<string>> p;
  vector<bool> is_final;
  string alphas = d.get_alphabet().to_string();
  set<string> finals_set = d.get_final_states();
  set<string> states = d.get_states();
  int max_state = states.size();

  vector<string> not_finals;

  for (auto it = states.begin(); it != states.end(); ++it) {
    auto find_it = find(finals_set.begin(), finals_set.end(), *it);
    if (find_it == finals_set.end()) {
      not_finals.push_back(*it);
    }
  }

  vector<string> finals{finals_set.begin(), finals_set.end()};

  p.push_back(finals);
  is_final.push_back(true);

  DFA new_d(d);
  {
    bool new_state{};
    vector<string> all_states{states.begin(), states.end()};
    for (string state: all_states) {

      for (char alpha: alphas) {

        if (!d.has_trans(state, alpha)) {
          new_state = true;
          break;
        }
      }
      if (new_state)
        break;
    }

    if (new_state) {

      not_finals.push_back(to_string(max_state));
      new_d.create_state(to_string(max_state));
      for (char alpha: alphas) {
        new_d.set_trans(to_string(max_state), alpha, to_string(max_state));
      }

      for (string state: all_states) {
        for (char alpha: alphas) {
          if (!d.has_trans(state, alpha)) {
            new_d.set_trans(state, alpha, to_string(max_state));
          }
        }
      }
    }
  }

  p.push_back(not_finals);

  is_final.push_back(false);
  while (true) {
    final_trans.clear();
    vector<vector<string>> new_p;
    vector<vector<int>> new_div;
    for (vector<string> cur_p: p) {
      vector<vector<string>> cur_trans;

      for (string state: cur_p) {
        vector<string> cur_t{};
        for (char alpha: alphas) {
            cur_t.push_back(new_d.get_trans(state, alpha));
        }
        cur_trans.push_back(cur_t);
      }
      vector<vector<string>> cur_p_div = translate(p, cur_p, cur_trans);
      new_p.insert(new_p.end(), cur_p_div.begin(), cur_p_div.end());
    }

    if (new_p.size() == p.size())
      break;
    p = new_p;
  }
  
  DFA res_d(new_d.get_alphabet());
  for (size_t i = 0; i < p.size(); ++i) {
    res_d.create_state(to_string(i));
    
    auto it = find(p[i].begin(), p[i].end(), new_d.get_initial_state());
    if (it != p[i].end())
      res_d.set_initial(to_string(i));

    for (string state: finals) {
      auto it = find(p[i].begin(), p[i].end(), state);
      if (it != p[i].end())
        res_d.make_final(to_string(i));
    }
  }

  res_d = del_states(res_d, alphas);

  return res_d;
}
