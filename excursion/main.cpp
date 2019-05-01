/************************************************************************************
    Min Cost Flow (or Min Cost Max Flow) algorithm with
    Dijkstra algorithm (with potentials) as shortest path search method.
    (Dijkstra for dense graphs running in O(N^2))
    Works O(N ^ 5). Less on practice.
    Runs in O(N ^ 3) for bipartite matching case.
    Based on problem 394 from informatics.mccme.ru
    http://informatics.mccme.ru//mod/statements/view3.php?chapterid=394
************************************************************************************/

#include <vector>
#include <cstdio>
#include <functional>
#include <queue>
#include <iostream>
#include <set>


using namespace std;
int n, s, f, t;

struct Edge {
    Edge(int _a, int _b, int _c, int _f, int _w) {
        a = _a;
        b = _b;
        c = _c;
        f = _f;
        w = _w;
    }

    ~Edge() {};
    int a; //from
    int b; //to
    int c; //capacity
    int f; //flow
    int w; //weight
    Edge *r;
};

const int MAX_NODES = 2000;
const int MAX_DIST = 2000000; //do not choose INT_MAX because you are adding weights to it
vector<vector<Edge *>> adj;
vector<int> distances;
vector<Edge *> parents;


bool find_path(int from, int to, vector<Edge *> &output) {
    distances.clear();
    distances.resize(n+1, MAX_DIST );
    distances[from] = 0;

    bool updated = true;
    while (updated) {
        updated = false;
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < (int) adj[j].size(); ++k) {
                Edge *e = adj[j][k];
                if (e->f <e->c)
                if (distances[e->b] > distances[e->a] + e->w) {
                    distances[e->b] = distances[e->a] + e->w;
                    parents[e->b] = e;
                    updated = true;
                }
            }
    }
    output.clear();
    if (distances[to] == MAX_DIST ) return false;
    int cur = to;
    while (parents[cur]) {
        output.push_back(parents[cur]);
        cur = parents[cur]->a;
    }
    return true;
}

int min_cost_max_flow() {
    int total_cost = 0;
    vector<Edge *> p;
    int myF=0;
    while (find_path(s, f, p)) {
        int flow = INT_MAX;
        for (int i = 0; i < p.size(); ++i)
            if (p[i]->c - p[i]->f < flow) flow = p[i]->c - p[i]->f;

        int cost = 0;
        for (int i = 0; i < p.size(); ++i) {
            cost += p[i]->w;
            p[i]->f += flow;
            p[i]->r->f -= flow;
        }
        cost *= flow; //cost per flow
        total_cost += cost;
        myF=flow;
    }
  cout<<total_cost<<" "<<myF;
}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> n >> s >> f;
    int u, v, c, flow;

    t = n * 2 + 1;
    adj.resize(t , vector<Edge *>());
    parents.resize(t , (Edge *) 0);


    for (int i = 0; i < n; i++) {

        cin >> u >> v >> flow >> c;
        Edge *e = new Edge(u, v, flow, 0, c);
        Edge *re = new Edge(v, u, 0, 0, -c);
        e->r = re;
        re->r = e;
        adj[u].push_back(e);
        adj[v].push_back(re);


    }
    cout << min_cost_max_flow() << endl;


    return 0;
}