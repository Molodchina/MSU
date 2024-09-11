#include "api.hpp"
#include <string>
#include <iostream>
#include <set>
#include <stack>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

using std::vector, std::pair, std::string, std::to_string, std::stack, std::cout, std::endl, std::count, std::map;

int cur_value;
vector<char> mapping(1000);


struct result {
  vector<int> firstpos;
  vector<int> lastpos;
  vector<vector<int>> cur_connections = vector<vector<int>> (1000);
  bool is_nullable = false;
};


// Func from https://stackoverflow.com/questions/19483663/vector-intersection-in-c
vector<int> intersect(vector<int> v1, vector<int> v2){
    vector<int> v3;

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::set_intersection(v1.begin(),v1.end(),
                          v2.begin(),v2.end(),
                          back_inserter(v3));
    return v3;
}


// Union from https://stackoverflow.com/questions/15916856/set-union-algorithm-using-vector-in-c
vector<int> unite(vector<int> v1, vector<int> v2){
    sort(v1.begin(), v1.end()); 
    sort(v2.begin(), v2.end()); 
  
    vector<int> v3(v1.size() 
                  + v2.size()); 
    auto it = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin()); 
  	v3.resize(it - v3.begin());

    return v3;
}


DFA build_dfa(const Alphabet &alphabet, const result &parse_reg) {
	string alphas = alphabet.to_string();
  size_t alpha_size = alphabet.size();
  vector<vector<int>> alpha_states;
	for (size_t i = 0; i < alpha_size; ++i)
		alpha_states.push_back(vector<int> ());

	for (size_t i = 0; i < cur_value; ++i) {
		size_t index = alphas.find(mapping[i], 0);
		if (index == std::string::npos) continue;
		alpha_states[index].push_back(i);
	}

	// cout << "alpha_states:" << endl;
	// for (size_t i = 0; i < alpha_size; ++i) {
	// 	cout << i << ":   ";
	// 	for (auto j: alpha_states[i])
	// 		cout << j << ", ";
	// 	cout << endl;
	// }
	
	DFA res = DFA(alphabet);
  size_t pos_states = 0;
  vector<vector<int>> states;
  vector<bool> end_states;

	states.push_back(parse_reg.firstpos);
	end_states.push_back(false);
  res.create_state(to_string(pos_states));
  res.set_initial(to_string(pos_states));
	auto it = std::find(parse_reg.firstpos.begin(), parse_reg.firstpos.end(), cur_value - 1);
	if (it != parse_reg.firstpos.end()) {
		end_states[end_states.size() - 1] = true;
		res.make_final(to_string(states.size() - 1));
	}

	while (pos_states < states.size()) {
		for (size_t pos_alpha = 0; pos_alpha < alpha_size; ++pos_alpha) {

			// cout << "states[pos_states]: " << pos_states << endl;
			// for (auto i: states[pos_states])
			// 	cout << i << ", ";
			// cout << endl;

			// cout << "alpha_states[pos_alpha]: " << pos_alpha << endl;
			// for (auto i: alpha_states[pos_alpha])
			// 	cout << i << ", ";
			// cout << endl;

			vector<int> state_intersect = intersect(states[pos_states], alpha_states[pos_alpha]);
			vector<int> cur_state;
			for (int state: state_intersect) {
				// cout << "parse_reg.cur_connections: " << state << endl;
				// for (auto i: parse_reg.cur_connections[state])
				// 	cout << i << ", ";
				// cout << endl;

				cur_state = unite(cur_state, parse_reg.cur_connections[state]);
			}
			// cout << "NEW state:" << endl;
			// for (auto i: cur_state)
			// 	cout << i << ", ";
			// cout << endl;
			if (!cur_state.size())
				continue;

			auto it = std::find(states.begin(), states.end(), cur_state);
			if (it == states.end()) {
				states.push_back(cur_state);
				end_states.push_back(false);
				res.create_state(to_string(states.size() - 1));
				res.set_trans(to_string(pos_states), alphas[pos_alpha], to_string(states.size() - 1));

				auto it = std::find(cur_state.begin(), cur_state.end(), cur_value - 1);
				if (it != cur_state.end()) {
					end_states[end_states.size() - 1] = true;
					res.make_final(to_string(states.size() - 1));
				}
			} else {
				size_t index = std::distance(states.begin(), it);
				res.set_trans(to_string(pos_states), alphas[pos_alpha], to_string(index));
			}
		}
		++pos_states;
	}

	// cout << "FINAL STATES:" << endl;
	// for (size_t i = 0; i < states.size(); ++i) {
	// 	cout << i << ":   ";
	// 	for (auto j: states[i])
	// 		cout << j << ", ";
	// 	cout << "   -> " << (int) (end_states[i]) << endl;
	// }

    return res;
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


result parse(const string &s) {
	result res;
	result cur_res;
	string new_s;
	for (size_t pos = 0; pos < s.length(); ++pos) {
		char c = s[pos];
		size_t cur_pos;

		switch (c) {
		case '(':
			cur_pos = find_end_parenth(s, pos);
			if (cur_pos == std::string::npos)
				exit(1);

			cur_pos -= pos + 1;

			cur_res = parse(s.substr(pos + 1, cur_pos));

			pos += cur_pos + 1;

			if (pos + 1 < s.length() && s[pos + 1] == '*') {
				++pos;
				goto iter_case;
			}
			break;
		case '|':
			cur_res = parse(s.substr(pos + 1));

			pos = s.length() - 1;

			res.firstpos = unite(res.firstpos, cur_res.firstpos);
			res.lastpos = unite(res.lastpos, cur_res.lastpos);

			for (int state = 0; state < cur_value; ++state)
				res.cur_connections[state] = unite(res.cur_connections[state], cur_res.cur_connections[state]);

			if (res.is_nullable || cur_res.is_nullable)
				res.is_nullable = true;
			cur_res = result ();

			continue;
		case '*':
		iter_case:
			if (!cur_res.firstpos.empty()) {
				for (int state: cur_res.lastpos)
					cur_res.cur_connections[state] = unite(cur_res.cur_connections[state], cur_res.firstpos);
				cur_res.is_nullable = true;
			} else if (!res.firstpos.empty()) {
				for (int state: res.lastpos)
					res.cur_connections[state] = unite(res.cur_connections[state], res.firstpos);
				res.is_nullable = true;
			}
			break;
		case '#':
			for (int state: res.lastpos)
				res.cur_connections[state].push_back(cur_value);
			res.lastpos = vector<int> {cur_value};
			if (res.is_nullable)
				res.firstpos.push_back(cur_value);
			mapping[cur_value++] = c;
			continue;
		case ')':
			break;
		case '_':
			cur_res.is_nullable = true;
			break;
		default:
			if (!cur_res.firstpos.empty()) {
				for (int state: cur_res.lastpos)
					cur_res.cur_connections[state].push_back(cur_value);
				cur_res.lastpos = vector<int> {cur_value};
			} else
				cur_res.firstpos = cur_res.lastpos = vector<int> {cur_value};
			mapping[cur_value++] = c;

			if (pos + 1 < s.length() && s[pos + 1] == '*') {
				++pos;
				goto iter_case;
			}

			break;
		}

		// cout << endl << "CUR STR: " << s.substr(0, pos) << endl;

		// cout << "CUR VALUE: " << cur_value - 1 << ' ' << c << endl;

		// cout << "CUR_RES.IS_NULLABLE: " << (int) cur_res.is_nullable << endl;


		// cout << "CUR_RES.firstpos:" << endl;
		// for (auto i: cur_res.firstpos)
		// 	cout << i << ", ";
		// cout << endl;

		// cout << "CUR_RES.lastpos:" << endl;
		// for (auto i: cur_res.lastpos)
		// 	cout << i << ", ";
		// cout << endl;

		// cout << "CUR_RES.cur_connections:" << endl;
		// for (size_t i = 0; i < 12; ++i) {
		// 	cout << i << ":   ";
		// 	for (auto j: cur_res.cur_connections[i])
		// 		cout << j << ", ";
		// 	cout << endl;
		// }

		// cout << endl << "RES.IS_NULLABLE: " << (int) res.is_nullable << endl;

		// cout << "RES.firstpos:" << endl;
		// for (auto i: res.firstpos)
		// 	cout << i << ", ";
		// cout << endl;

		// cout << "RES.lastpos:" << endl;
		// for (auto i: res.lastpos)
		// 	cout << i << ", ";
		// cout << endl;

		// cout << "RES.cur_connections:" << endl;
		// for (size_t i = 0; i < 12; ++i) {
		// 	cout << i << ":   ";
		// 	for (auto j: res.cur_connections[i])
		// 		cout << j << ", ";
		// 	cout << endl;
		// }

		for (int state: res.lastpos)
			res.cur_connections[state] = unite(res.cur_connections[state], cur_res.firstpos);

		for (int state = 0; state < cur_value; ++state)
			res.cur_connections[state] = unite(res.cur_connections[state], cur_res.cur_connections[state]);

		if (!cur_res.lastpos.empty()) {
			if (res.is_nullable)
				res.firstpos = unite(res.firstpos, cur_res.firstpos);

			if (cur_res.is_nullable)
				res.lastpos = unite(res.lastpos, cur_res.lastpos);
			else
				res.lastpos = cur_res.lastpos;
		}
		if (res.firstpos.empty()) {
			res.firstpos = cur_res.firstpos;
			res.is_nullable = cur_res.is_nullable;
		}

		if (!res.is_nullable || !cur_res.is_nullable)
			res.is_nullable = false;

		cur_res = result ();

		// cout << endl << "AFTER_RES.IS_NULLABLE: " << (int) res.is_nullable << endl;

		// cout << "AFTER_RES.firstpos:" << endl;
		// for (auto i: res.firstpos)
		// 	cout << i << ", ";
		// cout << endl;

		// cout << "AFTER_RES.lastpos:" << endl;
		// for (auto i: res.lastpos)
		// 	cout << i << ", ";
		// cout << endl;

		// cout << "AFTER_RES.cur_connections:" << endl;
		// for (size_t i = 0; i < 12; ++i) {
		// 	cout << i << ":   ";
		// 	for (auto j: res.cur_connections[i])
		// 		cout << j << ", ";
		// 	cout << endl;
		// }
	}

	// cout << "TMP_STRING: " << s << endl;

	// cout << "IS_NULLABLE: " << (int) res.is_nullable << endl;

	// cout << "TMP_RES.firstpos:" << endl;
	// for (auto i: res.firstpos)
	// 	cout << i << ", ";
	// cout << endl;

	// cout << "TMP_RES.lastpos:" << endl;
	// for (auto i: res.lastpos)
	// 	cout << i << ", ";
	// cout << endl;

	// cout << "TMP_RES.cur_connections:" << endl;
	// for (size_t i = 0; i < 12; ++i) {
	// 	cout << i << ":   ";
	// 	for (auto j: res.cur_connections[i])
	// 		cout << j << ", ";
	// 	cout << endl;
	// }

	return res;
}


string insert_eps(const string &s) {
	if (!s.size()) return "";

	std::stringstream ss;

	if (s[0] == '|')
		ss << '_';
	ss << s[0];
	for (size_t i = 1; i < s.size(); ++i) {
		switch(s[i]) {
		case ')':
			if (s[i - 1] == '(' || s[i - 1] == '|')
				ss << '_';
			break;
		case '|':
			if (s[i - 1] == '(' || s[i - 1] == '|')
				ss << '_';
		default:
			break;
		}
		ss << s[i];
	}
	return ss.str();
}


DFA re2dfa(const std::string &s) {
	string tmp_s = "(" + insert_eps(s) + ")#";

	if (tmp_s.length() == 3) {
		DFA res = DFA(Alphabet {"a"});
		res.create_state("0", true);
		return res;
	}

	result parse_reg = parse(tmp_s);

	// cout << endl << "MAPPING:" << endl;
	// for (size_t i = 0; i < cur_value; ++i)
	// 	cout << i << " - " << mapping[i] << endl;
	// cout << endl;

	// cout << "IS_NULLABLE: " << parse_reg.is_nullable << endl;

	// cout << "PARSE_RES.firstpos:" << endl;
	// for (auto i: parse_reg.firstpos)
	// 	cout << i << ", ";
	// cout << endl;

	// cout << "PARSE_RES.lastpos:" << endl;
	// for (auto i: parse_reg.lastpos)
	// 	cout << i << ", ";
	// cout << endl;

	// cout << "PARSE_RES.cur_connections:" << endl;
	// for (size_t i = 0; i < cur_value; ++i) {
	// 	cout << i << ":   ";
	// 	for (auto j: parse_reg.cur_connections[i])
	// 		cout << j << ", ";
	// 	cout << endl;
	// }

	if (parse_reg.firstpos.empty()) {
		DFA res = DFA(Alphabet {"a"});
		res.create_state("0", true);
		return res;
	}

	Alphabet alphabet(s);
  return build_dfa(alphabet, parse_reg);
}
