#include <bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f

typedef pair<long, long> iPair;

void addEdge(vector<pair<long, long>> adj[], long u, long v,
             long wt)
{
    adj[u].emplace_back(v, wt);
}

void shortestPath(vector<pair<long, long>> adj[], long V,
                  long src)
{
    priority_queue<iPair, vector<iPair>, greater<>> pq;

    vector<long> dist(V, INF);

    pq.emplace(pair(0, src));
    dist[src] = 0;

    while (!pq.empty()) {
        long u = pq.top().second;
        pq.pop();

        for (auto x: adj[u]) {
            long v = x.first;
            long weight = x.second;

            if (dist[v] > dist[u] + weight){
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
            }
        }
    }

    long res = *std::max_element(dist.begin(), dist.end());
    if (res == INF)
        cout << -1 << endl;
    else
        printf("%ld\n", res);
}

int main()
{
    long V, pos;
    cin >> V >> pos;
    vector<iPair> adj[V];
    long n;
    cin >> n;
    for (long i = 0; i < n; ++i) {
        long a, b, c;
        cin >> a >> b >> c;
        addEdge(adj, a - 1, b - 1, c);
    }

    shortestPath(adj, V, pos - 1);

    return 0;
}
