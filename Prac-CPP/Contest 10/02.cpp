#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

using std::string, std::cin, std::cout, std::endl, std::vector,
        std::pair, std::priority_queue;

void addEdge(vector<vector<int>> &adj, char u, char len)
{
    adj[(int) (u - 'A')].emplace_back((int) (len - 'A'));
}

bool non_term(char c) {
    return c >= 'A' && c <= 'Z';
}

bool eps(const string &s) {
    return any_of(s.begin(), s.end(), [](char c) { return c == '_'; });
}

void findPath(const vector<pair<char, string>> &v,
              vector<vector<int>> &adj, char S)
{
    int src = (int) (S - 'A');
    int len = (int) ('Z' - 'A' + 1);

    priority_queue<int, vector<int>> pq;
    vector<bool> dist(len, {});

    pq.emplace(src);
    dist[src] = true;

    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();

        for (auto n: adj[u]) {
            if (!dist[n]) {
                dist[n] = true;
                pq.emplace(n);
            }
        }
    }

    for (auto [i, j]: v) {
        if (dist[(int) (i - 'A')])
            cout << i << ' ' << j << endl;
    }
}

int main() {
    vector<vector<int>> adj{(size_t) ('Z' - 'A' + 1)};
    vector<pair<char, string>> v;

    string r;
    char l;
    while(cin >> l >> r) {
        if (eps(r)) {
            v.emplace_back(l, r);
            continue;
        }

        v.emplace_back(l, r);

        for (char j: r) {
            if (non_term(j))
                addEdge(adj, l, j);
        }
    }

    findPath(v, adj, 'S');

    return 0;
}
