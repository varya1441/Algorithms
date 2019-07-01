#include <iostream>
#include <cstdio>
#include <queue>
#include <iostream>
#include <bitset>

using namespace std;

vector<int> mt;

int n, m;


vector<int> min_ch, min_nech;
vector<vector<int>> g;
vector<bool> met_ch, met_nech;

void bfs() {
    queue<pair<int, bool>> que;
    que.emplace(make_pair(1, true));


    while (!que.empty()) {
        auto u = que.front();
        que.pop();
        int curr;
        if (u.second) {
            curr = min_ch[u.first];
        } else {
            curr = min_nech[u.first];
        }

        for (int v : g[u.first]) {
            if (u.second) {
                if (!met_nech[v]) {
                    met_nech[v] = true;
                    min_nech[v] = curr + 1;
                    que.emplace(make_pair(v, false));
                }
            } else {
                if (!met_ch[v]) {
                    met_ch[v] = true;
                    min_ch[v] = curr + 1;
                    que.emplace(make_pair(v, true));
                }
            }
        }

    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    int x, y;
    mt.assign(n + 1, -1);
    g.resize(n + 1);
    for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }

    met_ch.assign(n + 1, false);
    met_nech.assign(n + 1, false);
    min_ch.assign(n + 1, INT32_MAX);
    min_nech.assign(n + 1, INT32_MAX);
    met_ch[1] = true;
    //min_nech[1] = 0;
    min_ch[1] = 0;
    bfs();
    int col;
    cin >> col;
    int to, steps;
    for (int j = 0; j < col; ++j) {
        cin >> to >> steps;
        if (to == 1 && g[1].empty()) {
            if (steps > 0) {
                cout << "No" << endl;
            } else {
                cout << "Yes" << endl;
            }
        } else {
            if (steps % 2 == 0) {
                if (min_ch[to] >= steps) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
            } else {
                if (min_nech[to] >= steps) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
            }
        }
    }
    return 0;
}
