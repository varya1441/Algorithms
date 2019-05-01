
#include <vector>
#include <cstdio>
#include <functional>
#include <queue>
#include <iostream>
#include <set>

using namespace std;;
vector<int> visited;

void shortestPath( vector< vector<pair<int, int>>>adj,int last) {

    set<pair<long long, int>> pq;


    auto *dist = new long long[last + 1];
    for (int i = 0; i < last; ++i) {
        dist[i] = LLONG_MAX;
    }


    pq.insert(make_pair(0, 1));

    dist[1] = 0;


    while (!pq.empty()) {

        long long u = pq.begin()->second;
        pq.erase(pq.begin());


        for (auto x : adj[u]) {
            long long weight = x.second;
            int v = x.first;


            if ((dist[v] > dist[u] + weight)) {
                if (dist[v] != LLONG_MAX)
                    pq.erase(pq.find(make_pair(dist[v], v)));

                dist[v] = dist[u] + weight;
                pq.insert(make_pair(dist[v], v));
            }
        }
    }


    cout << dist[last - 1];
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

   int n, first = 1, m;
    cin >> n >> m;
    int x, y, v;
    vector<vector<pair<int, int>>> adj(static_cast<unsigned int>(n + 1));
    //  adj.resize(n + 1, vector<pair<long long, long long>>());
    for (int i = 0; i < m; ++i) {
        cin >> x >> y >> v;
        adj[x].emplace_back(y, v);
        adj[y].emplace_back(x, v);

    }
    shortestPath(adj, n + 1);

    return 0;
}