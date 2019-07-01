#include <iostream>
#include <string.h>
#include <algorithm>
#include <list>
#include <vector>
#include <map>
#include <assert.h>

using namespace std;
int n, m;

vector<int> del;
vector<vector<char>> adj;


int mask[200];
bool vis[200];

map<vector<int>, bool> a;
bool usedEdge[12345];
void rec(int edge, int s,vector < int > &ans) {
    if (edge == ans.size()) {
        for_each(ans.begin(),ans.end(),[](int ans){cout<<ans<<" ";});
        return ;
    }
    for (int e:adj[edge]) {
        if (!usedEdge[e]) {
            usedEdge[e] = true;
            vector < int > new_ans(ans.size());
            new_ans.operator=(ans);
            new_ans.emplace_back(e);
            rec(edge + 1, e, (new_ans));
            usedEdge[e] = false;
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    short u, v, f, s;
    cin >> n >> m;

    adj.resize(n, vector<char>());

    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);

    }
    vector<int>an(n);
    rec(0,5, an);

    return 0;
}