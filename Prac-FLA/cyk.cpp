#include <map>
#include <stack>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include <set>
#include <algorithm>


using namespace std;


template <typename T>
vector<T> unite(vector<T> v1, vector<T> v2){
    sort(v1.begin(), v1.end()); 
    sort(v2.begin(), v2.end());
  	
    v1.erase(unique(v1.begin(), v1.end()), v1.end());
    v2.erase(unique(v2.begin(), v2.end()), v2.end());

    vector<T> v3(v1.size() 
                  + v2.size()); 
    auto it = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin()); 
  	v3.resize(it - v3.begin());

    return v3;
}


// is_final is originally from https://stackoverflow.com/questions/9383788/check-stdstring-whether-contains-any-lowercase-character
bool if_final(const string& s) {
	return all_of(s.begin(), s.end(), [&](char c) {
		        return ((c >= 'A') && (c <= 'Z'));
		    });
}

bool if_lower(const char& ch) {
	return ((ch < 'A') || (ch > 'Z'));
}

bool if_eps(const string& strToCheck, const map<string, bool>& eps_rules) {
	return any_of(strToCheck.begin(), strToCheck.end(), [&](char c) {
		        return eps_rules.count(string {c}) > 0;
		    });
}


bool if_generative(const string& strToCheck, const vector<string>& gens) {
	return all_of(strToCheck.begin(), strToCheck.end(), [&](char c) {
		        return ((find(gens.begin(), gens.end(), string {c}) != gens.end()) || (c < 'A') || (c > 'Z'));
		    });
}


char new_left(const map<string, vector<string>>& rules,
				const map<string, vector<string>>& new_rules) {
	for (char ch = 'A'; ch <= 'Z'; ++ch)
		if ((!rules.count(string {ch})) && (!new_rules.count(string {ch})))
			return ch;
	return '=';
}


void remove_eps(map<string, vector<string>>& rules) {
	map<string, bool> eps_rules;
	for (auto& [left, right]: rules) {
		for (auto it = right.begin(); it != right.end(); ) {
			if (*it == string{"_"}) {
				eps_rules.emplace(left, true);
				it = right.erase(it);
			} else
				++it;
		}
	}
	// cout << "AFTER FIND EPS-PROD" << endl;
	// for (const auto& rule : rules) {
    //     std::cout << "Key: " << rule.first << std::endl;
    //     std::cout << "Rules:" << std::endl;
    //     for (const auto& r : rule.second) {
    //         std::cout << "\t" << r << std::endl;
    //     }
    // }

	{
		bool changed_fl = true;
		while (changed_fl) {
			changed_fl = false;
			for (auto&  [left, right]: rules) {
				if (eps_rules.count(left))
					continue;

				for (auto it = right.begin(); it != right.end(); ++it) {
					int amount = 0;
					for (const char& sym: *it)
						amount += (int) (eps_rules.count(string {sym}) > 0);
					if (amount == (*it).size()) {
						eps_rules.emplace(left, true);
						changed_fl = true;
						break;
					}
				}
			}
		}
	}
    // cout << "eps_rules: ";
    // for (auto eps: eps_rules)
    // 	cout << eps.first << " ";
    // cout << endl;

	// Create eps-rules invariants
	for (auto& [left, right]: rules) {
		stack<string> split_rules;
		// cout << "split_rules: ";
		for (const string& rule: right) {
			if (if_eps(rule, eps_rules)) {
				split_rules.push(rule);
	    		// cout << rule << " ";
			}
		}
	    // cout << endl;

		vector<string> checked;
		while(!split_rules.empty()) {
			string rule = split_rules.top();
      		split_rules.pop();
      		if (find(checked.begin(), checked.end(), rule) != checked.end())
      			continue;

      		vector<string> invars;
      		for (size_t pos = 0; pos < rule.size(); ++pos) {
      			if (eps_rules.count(string {rule[pos]})) {
      				string invar = rule;
			        invar.erase(pos, 1);
			        if ((find(right.begin(), right.end(), invar) == right.end()) && (invar.size()))
	      				invars.push_back(invar);
	      			split_rules.push(invar);
      			}
      		}
      		checked.push_back(rule);
      		// if (invars.size()) {
      		// 	cout << "invars: ";
			//     for (auto rule: invars)
			//     	cout << rule << " ";
			//     cout << endl;
      		// }
      		right = unite(right, invars);
		}
	}
	if (eps_rules.count(string {"S"}))
		rules.emplace("#", vector<string> {"S", "_"});
	cout << "AFTER REMOVE EPS-RULES" << endl;
	for (const auto& rule : rules) {
        std::cout << "Key: " << rule.first << std::endl;
        std::cout << "Rules:" << std::endl;
        for (const auto& r : rule.second) {
            std::cout << "\t" << r << std::endl;
        }
    }
}


void remove_chains(map<string, vector<string>>& rules) {
	vector<pair<string, string>> chains;
	map<string, vector<string>> chain_rules;
	map<string, vector<string>> other_rules;
	for (auto& [left, right]: rules) {
		chains.emplace_back(left, left);
		for (auto it = right.begin(); it != right.end(); ++it) {
			if (((*it).size() == 1) && (if_final(*it))) {
				if (chain_rules.count(left))
					chain_rules[left].push_back(*it);
				else
					chain_rules.emplace(left, vector<string> {*it});
			} else {
				if (other_rules.count(left))
					other_rules[left].push_back(*it);
				else
					other_rules.emplace(left, vector<string> {*it});
			}
		}
	}
	// cout << "CHAIN RULES" << endl;
	// for (const auto& rule : chain_rules) {
    //     std::cout << "Key: " << rule.first << std::endl;
    //     std::cout << "Rules:" << std::endl;
    //     for (const auto& r : rule.second) {
    //         std::cout << "\t" << r << std::endl;
    //     }
    // }
    // cout << "OTHER RULES" << endl;
	// for (const auto& rule : other_rules) {
    //     std::cout << "Key: " << rule.first << std::endl;
    //     std::cout << "Rules:" << std::endl;
    //     for (const auto& r : rule.second) {
    //         std::cout << "\t" << r << std::endl;
    //     }
    // }

	while (true) {
		vector<pair<string, string>> new_chains;
		for (auto& [left, right]: chain_rules) {
			for (auto& [init, end]: chains) {
				if (left == end)
					for (auto rule: right)
						new_chains.emplace_back(init, rule);
			}
		}
		new_chains = unite(chains, new_chains);
		if (chains.size() == new_chains.size())
			break;
		chains = new_chains;
	}

	cout << "CHAINS" << endl;
	for (auto& [init, end]: chains)
        cout << init << " " << end << endl;

	for (auto& [init, end]: chains) {
		for (auto& [left, right]: other_rules) {
			if (left == init) {
				right = unite(right, other_rules[end]);
			}
		}
	}
	rules = other_rules;
	cout << "AFTER REMOVE CHAIN-PRODS" << endl;
	for (const auto& rule : rules) {
	    std::cout << "Key: " << rule.first << std::endl;
	    std::cout << "Rules:" << std::endl;
	    for (const auto& r : rule.second) {
	        std::cout << "\t" << r << std::endl;
	    }
	}
}


void remove_ingen(map<string, vector<string>>& rules) {
	vector<string> gens;
	bool changed_fl = true;
	while(changed_fl) {
		changed_fl = false;
		for (auto& [left, right]: rules) {
			if (find(gens.begin(), gens.end(), left) != gens.end())
				continue;

			for (auto const& rule: right) {
				if (if_generative(rule, gens)) {
					gens.push_back(left);
					changed_fl = true;
					break;
				}
			}
		}
	}

	for (auto it = rules.begin(); it != rules.end(); ) {
		if (find(gens.begin(), gens.end(), (*it).first) == gens.end()) {
			it = rules.erase(it);
			continue;
		}

		for (auto rule_it = (*it).second.begin(); rule_it != (*it).second.end(); )
			if (!if_generative(*rule_it, gens))
				rule_it = (*it).second.erase(rule_it);
			else
				++rule_it;
		++it;
	}
	cout << "AFTER REMOVE USELESS SYMBOLS" << endl;
	for (const auto& rule : rules) {
        std::cout << "Key: " << rule.first << std::endl;
        std::cout << "Rules:" << std::endl;
        for (const auto& r : rule.second) {
            std::cout << "\t" << r << std::endl;
        }
    }
}


void remove_unreach(map<string, vector<string>>& rules) {
	stack<string> reach;
	reach.push("S");
	map<string, bool> checked;
	while (!reach.empty()) {
		string cur = reach.top();
		reach.pop();
		if (checked.count(cur))
			continue;

		for (const string& rule: rules[cur])
			for (const char& ch: rule)
				if (string str = string {ch}; if_final(str))
					reach.emplace(str);

		checked[string {cur}] = true;
	}

	for (auto it = rules.begin(); it != rules.end(); ) {
		if ((!checked.count((*it).first)) && ((*it).first != "#"))
			it = rules.erase(it);
		else
			++it;
	}
	cout << "AFTER REMOVE UNREACH SYMBOLS" << endl;
	for (const auto& rule : rules) {
        std::cout << "Key: " << rule.first << std::endl;
        std::cout << "Rules:" << std::endl;
        for (const auto& r : rule.second) {
            std::cout << "\t" << r << std::endl;
        }
    }
}


void remove_long(map<string, vector<string>>& rules) {
	map<string, string> simple_rules;
	for (auto& [left, right]: rules)
		if ((right.size() == 1) && (((right[0].size() == 1) && ((right[0][0] < 'A') || right[0][0] > 'Z')) 
				|| ((if_final(right[0])) && (right[0].size() == 2))))
			simple_rules.emplace(right[0], left);
	
	if (simple_rules.size()) {
		cout << "SIMPLE RULES:" << endl;
		for (const auto& rule : simple_rules)
	        std::cout << "Key: " << rule.first << " - " << rule.second<< endl;
	}

	map<string, vector<string>> new_rules;
	for (auto& [left, right]: rules) {
		for (string& rule: right) {
			cout << endl << "RULE: " << rule << endl;

			if (rule.size() > 2) {
				string tmp_rule{rule};
				char prev_state;
				for (size_t i = 0; i < tmp_rule.size() - 2; ++i) {
					char tmp_ch{tmp_rule[i]};
					if (if_lower(tmp_ch)) {
						if (simple_rules.count(string {tmp_ch}))
							tmp_ch = simple_rules[string {tmp_ch}][0];
						else {
							tmp_ch = new_left(rules, new_rules);
							new_rules.emplace(string {tmp_ch}, vector<string> {string {tmp_rule[i]}});
							simple_rules[string {tmp_rule[i]}] = tmp_ch;
						}
					}
					
					char new_state = new_left(rules, new_rules);
					if (!i) {
						rule = string() + tmp_ch + new_state;
						simple_rules[left] = rule;

						cout << left << " " << rule << endl;
					} else {
						string str{string() + tmp_ch + new_state};
						new_rules[string {prev_state}].push_back(str);
						simple_rules[str] = string {prev_state};

						cout << prev_state << " " << str << endl;
					}
					new_rules.emplace(string {new_state}, vector<string> {});
					prev_state = new_state;
				}
				size_t pos = tmp_rule.size() - 2;	
				char tmp_ch1{tmp_rule[pos]};
				if (if_lower(tmp_ch1)) {
					if (simple_rules.count(string {tmp_ch1}))
						tmp_ch1 = simple_rules[string {tmp_ch1}][0];
					else {
						tmp_ch1 = new_left(rules, new_rules);
						new_rules.emplace(string {tmp_ch1}, vector<string> {string {tmp_rule[pos]}});
						simple_rules[string {tmp_rule[pos]}] = tmp_ch1;
					}
				}
				++pos;
				char tmp_ch2{tmp_rule[pos]};
				if (if_lower(tmp_ch2)) {
					if (simple_rules.count(string {tmp_ch2}))
						tmp_ch2 = simple_rules[string {tmp_ch2}][0];
					else {
						tmp_ch2 = new_left(rules, new_rules);
						new_rules.emplace(string {tmp_ch2}, vector<string> {string {tmp_rule[pos]}});
						simple_rules[string {tmp_rule[pos]}] = tmp_ch2;
						++pos;
					}
				}
				new_rules[string {prev_state}].push_back(string {string() + tmp_ch1 + tmp_ch2});
				
				cout << prev_state << " " << string {string() + tmp_ch1 + tmp_ch2} << endl;

			} else if ((rule.size() == 2) && (any_of(rule.begin(), rule.end(), ::if_lower))) {
				if (if_lower(rule[0])) {
					string tmp = string {rule[0]};
					if (simple_rules.count(tmp))
						rule[0] = simple_rules[tmp][0];
					else {
						rule[0] = new_left(rules, new_rules);
						new_rules.emplace(string {rule[0]}, vector<string> {string {tmp}});
						simple_rules[tmp] = rule[0];
					}
				} 
				if (if_lower(rule[1])) {
					string tmp = string {rule[1]};
					if (simple_rules.count(tmp))
						rule[1] = simple_rules[tmp][0];
					else {
						rule[1] = new_left(rules, new_rules);
						new_rules.emplace(string {rule[1]}, vector<string> {string {tmp}});
						simple_rules[tmp] = rule[1];
					}
				}

				cout << left << " " << rule << endl;
			}
		}
		cout << "NEW RULES: " << left << endl;
		for (const auto& rule : new_rules) {
	        std::cout << "Key: " << rule.first << std::endl;
	        std::cout << "Rules:" << std::endl;
	        for (const auto& r : rule.second) {
	            std::cout << "\t" << r << std::endl;
	        }
	    }
	}
	rules.insert(new_rules.begin(), new_rules.end());
	cout << "AFTER REMOVE LONG RULES" << endl;
	for (const auto& rule : rules) {
        std::cout << "Key: " << rule.first << std::endl;
        std::cout << "Rules:" << std::endl;
        for (const auto& r : rule.second) {
            std::cout << "\t" << r << std::endl;
        }
    }
}


void fix_rules(map<string, vector<string>>& rules) {
	remove_eps(rules);
	remove_chains(rules);
	remove_ingen(rules);
	remove_unreach(rules);
	remove_long(rules);
}


size_t counr_lower(const string& s) {
	size_t lower = 0;
	for (const auto& ch: s)
		if (ch >= 'a' && ch <= 'z')
			++lower;
	return lower;
}


bool cykParse(const map<string, vector<string>>& rules, const string& word) {
    int n = word.size();
    if (word == "_") {
    	if (rules.count("#"))
    		return true;
    	return false;
	}
    map<string, vector<string>> swap;
    map<int, map<int, set<string>>> t;
    // Init t
	for (auto const& [left, right]: rules)
		for (const string& rule: right)
			if (swap.count(rule))
				swap[rule].push_back(left);
			else
				swap.emplace(rule, vector<string> {left});

	// cout << "SWAP" << endl;
	// for (const auto& rule : swap) {
    //     std::cout << "VAL: " << rule.first << std::endl;
    //     std::cout << "KEY:" << std::endl;
    //     for (const auto& r : rule.second) {
    //         std::cout << "\t" << r << std::endl;
    //     }
    // }

	for(int j = 0;j < n;j++) {
		if (string str = string {word[j]}; swap.count(str))
			t[j][j].insert(swap[str].begin(), swap[str].end());

		for(int i = j; i >= 0; --i) {
			for(int k = i; k <= j; ++k) {
				for (const string &left: t[i][k]) {
					for (const string &right: t[k + 1][j]) {
						if (string str = string() + left + right; swap.count(str))
							t[i][j].insert(swap[str].begin(), swap[str].end());
					}
				}
			}
		}
	}
	// if (n) {
	// 	cout << endl;
	// 	for (size_t j = 0; j < n; ++j)
	// 		cout << "\t" << j;
	// 	cout << endl;
	// 	for (size_t i = 0; i < n; ++i) {
	// 		cout << i << "\t";
	// 		for (size_t j = 0; j < n; ++j) {
	// 			cout << "{";
	// 			for (auto const& val: t[i][j])
	// 				cout << val << ", ";
	// 			cout << "}\t";
	// 		}
	// 		cout << endl;
	// 	}
	// }

	if (t[0][n - 1].size())
		return true;
	else
		return false;
}


int main() { 
	ifstream inputFile("cyk.in");
	if (!inputFile) { 
		cerr << "Unable to open input file cyk.in" << endl; 
		exit(1);
	}

	string word;
	getline(inputFile, word);

	map<string, vector<string>> rules;
    string line;
    while (getline(inputFile, line)) {
		istringstream line_stream(line);
		string left, right;
		line_stream >> left >> right;
		// cout << left << " " << right << endl;

	    if (rules.find(left) != rules.end()) {
	    	rules[left].push_back(right);
	    } else {
	       	rules.emplace(left, vector<string> {right});
	    }

	    if(inputFile.eof()) break;
	}
	inputFile.close(); 

	fix_rules(rules);
	cout << endl << "RES RULES" << endl;
	for (const auto& rule : rules) {
        std::cout << "Key: " << rule.first << std::endl;
        std::cout << "Rules:" << std::endl;
        for (const auto& r : rule.second) {
            std::cout << "\t" << r << std::endl;
        }
    }

	ofstream outputFile("cyk.out");
    if (!outputFile) { 
		cerr << "Unable to open output file cyk.in" << endl; 
		exit(2);
	}
	if (cykParse(rules, word))
		outputFile << "YES";
	else
		outputFile << "NO";

	return 0;
}