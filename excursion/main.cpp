#include <vector>
#include <cstdio>
#include <queue>
#include <iostream>

#include <cmath>

using namespace std;
int_fast16_t t, s, n;
const int_fast32_t inf = (INT32_MAX) / 2;

int_fast32_t calc(int_fast32_t);

struct Edgee {
    int_fast16_t to, cost, cap, backEdge;
    int_fast32_t flow;

    Edgee(int_fast16_t to, int_fast16_t cost, int_fast16_t cap, int_fast32_t flow, int_fast16_t backEdge) : to(to),
                                                                                                            cost(cost),
                                                                                                            cap(cap),
                                                                                                            flow(flow),
                                                                                                            backEdge(
                                                                                                                    backEdge) {}
};

int_fast16_t m = 0;
vector<vector<Edgee>> agj;

vector<Edgee> e;
vector<int_fast16_t> from, from_edge;

//1-calc/2-notcalc/0-ing
bool dijkstra() {

    vector<int_fast8_t> state(m, 2);
    from.assign(m, -1);
    vector<int_fast32_t> d(m, inf);
    from_edge.assign(m, -1);

    deque<int_fast16_t> q;

    q.push_back(s);
    d[s] = 0;
    while (!q.empty()) {
        auto v = q.front();
        q.pop_front();
        state[v] = 1;
        for (int_fast16_t i = 0; i < agj[v].size(); ++i) {
            auto &e = agj[v][i];
            auto to = e.to;
            auto co = e.cost + d[v];
            if ((e.flow < e.cap) && (d[to] > co)) {

                d[to] = co;
                from[to] = v;
                from_edge[to] = i;
                if (state[to] == 0) continue;
                if (state[to] == 1)
                    q.emplace_front(to);
                else if (state[to] == 2)
                    q.emplace_back(to);

                state[to] = 0;
            }
        }
    }

    return d[t] != inf;
}

void minCostMaxFlow() {
    int_fast32_t flow = 0, cost = 0;
    while (flow < inf) {

        if (!dijkstra()) {
            break;
        }

        auto addf = calc(flow);

        for (int_fast16_t it = t; it != s; it = from[it]) {
            auto fr = from[it];
            auto fe = from_edge[it];
            auto &ffe_b = agj[fr][fe].backEdge;

            agj[fr][fe].flow += addf;
            agj[it][ffe_b].flow -= addf;
            cost += agj[fr][fe].cost * addf;

        }
        flow += addf;
    }

    cout << flow << endl << cost;
}

int_fast32_t calc(int_fast32_t flow) {

    auto addf = inf - flow;
    for (int_fast16_t it = t; it != s; it = from[it]) {
        addf = min(addf, agj[from[it]][from_edge[it]].cap
                         - agj[from[it]][from_edge[it]].flow);

    }
    return addf;
}

//void add(int_fast16_t u,int_fast16_t v,int_fast16_t w,int_fast16_t c){
//    agj[u].push_back(Edgee(v, w, c, 0, (agj[v].size())));
//    agj[v].push_back(Edgee(u, -w, 0, 0, (agj[u].size())));
//}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int_fast16_t u, v, c, w;


    cin >> n >> s >> t;
    --s;
    --t;

    agj.resize(n);

    while (cin >> u) {

        cin >> v >> c >> w;
        --u;
        --v;

        Edgee uv(v, w, c, 0, (agj[v].size()));
        Edgee vu(u, -w, 0, 0, (agj[u].size()));
        agj[u].emplace_back(uv);
        agj[v].emplace_back(vu);
        Edgee uv2(u, w, c, 0, (agj[u].size()));
        Edgee vu2(v, -w, 0, 0, (agj[v].size()));
        agj[v].emplace_back(uv2);
        agj[u].emplace_back(vu2);

    }

    m = agj.size();
    from.resize(m + 1), from_edge.resize(m + 1);
    minCostMaxFlow();
    return 0;
}
