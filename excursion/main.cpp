#include <vector>
#include <cstdio>
#include <queue>
#include <iostream>
#include <set>

#include <cmath>

using namespace std;
int t, s, n;
const int inf = INT32_MAX;

struct Edgee {
    int to, cost, cap, flow, backEdge;

    Edgee(int to, int cost, int cap, int flow, int backEdge) : to(to), cost(cost), cap(cap), flow(flow),
                                                               backEdge(backEdge) {}
};

vector<vector<Edgee>> agj;
vector<int> state, from, from_edge, d;

bool dijkstra() {
    int head=0,tail=0;
    state.assign(n, 2), from.assign(n, -1), d.assign(n, inf);

    vector<int> q(n);

    d[s] = 0;
    state[s] = 1;
    q[tail]=s;
    tail++;
    while (head!=tail) {
        int v = q[head];
        head++;
        if(head==n) {
            head = 0;
        }
        state[v] = 0;

        for (int i = 0; i < (int) agj[v].size(); i++) {
            Edgee e = agj[v][i];
            if (e.flow >= e.cap || d[e.to] <= d[v] + e.cost)
                continue;
            int to = e.to;
            d[to] = d[v] + e.cost;
            from[to] = v;
            from_edge[to] = i;
            if (state[to] == 1) continue;
            if (!state[to]) {
                head--;
                if (head == -1)
                    head = n - 1;

                q.emplace(q.begin()+head,to);

            }
            else {

                q.emplace(q.begin() + tail, to);
                tail++;
                if (tail == n)
                    tail = 0;
            }
            state[to] = 1;
        }
    }
    return d[t] != inf;
}

void minCostMaxFlow() {

    long long flow = 0, cost = 0;
    while (dijkstra()) {


        int it = t, addf = inf;
        while (it != s) {
            addf = min(addf, agj[from[it]][from_edge[it]].cap
                             - agj[from[it]][from_edge[it]].flow);
            it = from[it];
        }
        it = t;
        while (it != s) {
            agj[from[it]][from_edge[it]].flow += addf;
            agj[it][agj[from[it]][from_edge[it]].backEdge].flow -= addf;
            cost += agj[from[it]][from_edge[it]].cost * addf;
            it = from[it];
        }
        flow += addf;
    }
    cout << flow << endl << cost;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int u, v, c, w;
    cin >> n >> s >> t;
    s--;
    t--;
    int counter;
    agj.resize(n + 1);
    state.resize(n), from.resize(n), from_edge.resize(n), d.resize(n);
    while (cin >> u) {
        u--;
        cin >> v >> c >> w;
        v--;
        agj[u].push_back(Edgee(v, w, c, 0, static_cast<int>(agj[v].size())));
        agj[v].push_back(Edgee(u, -w, 0, 0, static_cast<int>(agj[u].size())));
        agj[u].push_back(Edgee(v, -w, 0, 0, static_cast<int>(agj[v].size())));
        agj[v].push_back(Edgee(u, w, c, 0, static_cast<int>(agj[u].size())));


    }
    // n++;
    minCostMaxFlow();
    return 0;
}