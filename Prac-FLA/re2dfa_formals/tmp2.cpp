class ThompsonNFA {
public:
    DFA* buildNFA(const std::string& regex) {
        Alphabet alphabet(regex);
        DFA* nfa = new DFA(alphabet);

        std::stack<std::pair<std::string, std::string>> stack;
        std::map<std::string, std::pair<std::string, std::string>> transitions;

        std::string currentState = "0";
        nfa->create_state(currentState);
        nfa->set_initial(currentState);

        for (char c : regex) {
            if (c == '|' || c == '*' || c == ')') {
                std::pair<std::string, std::string> top = stack.top();
                stack.pop();

                if (c == '|') {
                    std::pair<std::string, std::string> second = stack.top();
                    stack.pop();

                    std::string newState = std::to_string(nfa->size());
                    nfa->create_state(newState);

                    nfa->set_trans(top.first, 'ε', newState);
                    nfa->set_trans(second.first, 'ε', newState);

                    top.first = newState;
                } else if (c == '*') {
                    std::string newState = std::to_string(nfa->size());
                    nfa->create_state(newState);

                    nfa->set_trans(top.first, 'ε', newState);
                    nfa->set_trans(newState, 'ε', top.second);

                    top.first = newState;
                }

                stack.push(top);
            } else if (c == '(') {
                stack.push({currentState, currentState});
            } else {
                std::string newState = std::to_string(nfa->size());
                nfa->create_state(newState);

                if (!stack.empty()) {
                    std::pair<std::string, std::string>& top = stack.top();
                    top.second = newState;
                }

                nfa->set_trans(currentState, c, newState);
                currentState = newState;
            }
        }

        nfa->make_final(currentState);
        return nfa;
    }
};