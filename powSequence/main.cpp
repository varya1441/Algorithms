#include <iostream>
#include <queue>
#include <bits/stl_vector.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int m, n;
    std::cin >> n >> m;
    std::vector<std::vector<int>> e(n);
    int u, v;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        --u;
        --v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    std::priority_queue<int> ans;
    for (int j = 0; j < n; ++j) {
        ans.emplace(e[j].size());
    }
    for (int k = 0; k <n; ++k) {
       std::cout<<ans.top()<<" ";
       ans.pop();
    }
    return 0;
}