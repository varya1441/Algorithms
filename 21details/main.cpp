#pragma warning(disable : 4996)

#include <vector>
#include <cstdio>
#include <functional>
#include <queue>
#include <iostream>
#include <cmath>


using namespace std;

vector<int32_t> detail;
vector<int_fast32_t> mash;

struct Node {
    int_fast32_t machine, time, last, remainder;


    Node(int_fast32_t machine, int_fast32_t time, int_fast32_t last, int_fast32_t remainder) : machine(machine),
                                                                                               time(time),
                                                                                               last(last),

};

int n, m;
vector<Node> ans;

void print(int_fast32_t i) {


    while (i != 0) {
        if (ans[i].machine != m) {
            while (ans[i].machine + 1 != m) {
                cout << -1 << " ";
                --m;
            }
            cout << detail[ans[i].last] << " ";
            --m;

        } else {

            cout << detail[ans[i].last] << "\n";
        }

        i -= (int_fast32_t) pow(2, ans[i].last);


    }
}

void optim() {
    queue<int_fast32_t> tree;
    int summ = 0;
    for (int i = 0; i < n; i++) {
        summ += detail[i];
    }

    ans.assign((int) pow(2, n), Node(INT_FAST32_MAX, INT_FAST32_MAX, 0, summ));

    ans[0] = Node(0, 0, -1, summ);
    tree.emplace(0);
    while (!tree.empty()) {
        int_fast32_t u = tree.front();
        tree.pop();
        int_fast32_t detail_min = INT_FAST32_MAX;
        for (int i = 0; i < n; ++i) {
            if ((u & ((int_fast32_t) pow(2, i))) == 0) {
                detail_min = min(detail_min, detail[i]);
            }
        }
        for (int j = 0; j < n; ++j) {
            if ((u & ((int_fast32_t) pow(2, j))) == 0) {
                int_fast32_t v = u + pow(2, j);

                if (ans[u].time + detail[j] <= ans[u].remainder / (m - ans[u].machine)) {

                    if (ans[u].machine != ans[v].machine) {
                        if (ans[u].machine < ans[v].machine) {
                            if (ans[v].machine == INT_FAST32_MAX) {
                                tree.emplace(v);
                            }
                            ans[v] = Node(ans[u].machine, detail[j] + ans[u].time, j, ans[u].remainder);
                        }
                    } else if (ans[u].time + detail[j] < ans[v].time) {
                        if (ans[v].machine == INT_FAST32_MAX) {
                            tree.emplace(v);
                        }
                        ans[v] = Node(ans[u].machine, detail[j] + ans[u].time, j, ans[u].remainder);
                    }

                } else if (ans[u].machine + 1 < m) {

                    Node t(ans[u].machine + 1, 0, 0,
                           ans[u].remainder - ans[u].time);

                    if (detail[j] <= t.remainder / (m - t.machine) || detail[j] == detail_min) {
                        if (t.machine != ans[v].machine) {
                            if (t.machine < ans[v].machine) {
                                if (ans[v].machine == INT_FAST32_MAX) {
                                    tree.emplace(v);
                                }
                                ans[v] = Node(t.machine, detail[j], j, t.remainder);
                            }
                        } else if (t.time + detail[j] < ans[v].time) {
                            if (ans[v].machine == INT_FAST32_MAX) {
                                tree.emplace(v);
                            }
                            ans[v] = Node(t.machine, detail[j], j, t.remainder);
                        }
                    }
                }
            }
        }
    }

    int_fast32_t i = (int_fast32_t) pow(2, n) - 1;
    cout << ans[i].time << "\n";
    print(i);

}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> n >> m;
    int_fast32_t elem;
    for (int i = 0; i < n; i++) {
        cin >> elem;
        detail.emplace_back(elem);
    }
    optim();
    return 0;
}