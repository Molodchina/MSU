#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <unordered_map>

struct Node {
    char symbol;
    int next;
};

std::vector<Node> nodes;
std::vector<int> start, end;
std::unordered_map<char, int> position;

int add_node(char symbol) {
    nodes.push_back({symbol, -1});
    return nodes.size() - 1;
}

void concat(int a, int b) {
    end[a] = start[b];
    end[b] = end[b];
    start[a] = start[a];
}

void closure(int a, int b) {
    end[a] = start[b];
    end[b] = end[b];
    start[b] = start[a];
}

void kleene(int a) {
    int b = add_node('\0');
    start.push_back(b);
    end.push_back(end[a]);
    closure(b, a);
}

void build_nfa(const std::string& regexp) {
    std::stack<int> s;
    int i = 0;
    while (i < regexp.size()) {
        if (regexp[i] == '(') {
            s.push(start.size());
            start.push_back(add_node('\0'));
        } else if (regexp[i] == ')') {
            int a = start.back();
            start.pop_back();
            int b = s.top();
            s.pop();
            concat(b, a);
        } else if (regexp[i] == '*') {
            int a = start.back();
            kleene(a);
        } else if (regexp[i] == '|') {
            int a = start.back();
            int b = add_node('\0');
            start.push_back(b);
            closure(a, b);
        } else {
            int a = start.back();
            int b = add_node(regexp[i]);
            concat(a, b);
        }
        i++;
    }
}

void print_nfa() {
    for (int i = 0; i < nodes.size(); i++) {
        std::cout << i << ": " << nodes[i].symbol << " -> " << nodes[i].next << std::endl;
    }
    std::cout << "Start: " << start[0] << std::endl;
    std::cout << "End: " << end[0] << std::endl;
}

int main() {
    std::string regexp = "(a|b)*";
    position['a'] = 0;
    position['b'] = 1;
    start.push_back(add_node('\0'));
    end.push_back(-1);
    build_nfa(regexp);
    print_nfa();
    return 0;
}
