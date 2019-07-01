#pragma warning(disable : 4996)

#include <stdio.h>

#include <vector>
#include <cstdio>
#include <functional>
#include <queue>
#include <iostream>
#include <set>

using namespace std;
long long time;
vector<bool> vis;
//b-1-false,p-0-true
vector<int> path;
int n, m;
struct Crossroads {
    Crossroads() {

    }

    bool color;
    int tiB;
    int tiP;
    int tiC;

    Crossroads(const bool &color, const int &tiB, const int &tiP, const int &tiC) :
            color(color), tiB(tiB), tiP(tiP), tiC(tiC) {}

    bool operator==(const Crossroads &rhs) const {
        return color == rhs.color &&
               tiB == rhs.tiB &&
               tiP == rhs.tiP &&
               tiC == rhs.tiC;
    }

    void switchColor() {
        color = !color;
    }

    bool operator!=(const Crossroads &rhs) const {
        return !(rhs == *this);
    }

    int getTimeColor() {
        if (color == false) {
            return tiB;
        }
        else
            return tiP;
    }

};

int ch(int t, Crossroads u, Crossroads v) {

    if (u.tiC <= v.tiC) {
        t = u.tiC;
        u.switchColor();

        u.tiC = u.getTimeColor();
        if (v.tiC - t <= 0) {


            v.switchColor();
            if (v.color != u.color) {
                t += min(v.getTimeColor(), u.getTimeColor());
                v.switchColor();
            }
        }
    }
    else {
        t = v.tiC;
        v.switchColor();

        v.tiC = v.getTimeColor();
        if (u.tiC - t <= 0) {


            u.switchColor();
            if (v.color != u.color) {
                t += min(v.getTimeColor(), u.getTimeColor());
                u.switchColor();
            }
        }
    }
    return t;


}

Crossroads getCurrentCr(Crossroads crossroads, int tim) {
    Crossroads cross(crossroads.color, crossroads.tiB, crossroads.tiP, crossroads.tiC);
    int t = tim;
    while (t - cross.tiC >= 0) {
        t -= cross.tiC;
        cross.switchColor();
        cross.tiC = cross.getTimeColor();
    }
    cross.tiC -= t;
    return cross;
}

int shortestPath(vector<vector<pair<int, int>>> adj, vector<Crossroads> crossroads, int last, int first) {

    set<pair<long long, int>> pq;


    auto *dist = new long long[n + 1];
    for (int i = 0; i < n; ++i) {
        dist[i] = LLONG_MAX;
    }


    pq.insert(make_pair(0, first));
    //  path[first]=first;
    dist[first] = 0;
    int tmp = 0;
    while (!pq.empty()) {

        long long u = pq.begin()->second;
        pq.erase(pq.begin());
        tmp = dist[u];
        vis[u] = true;
        for (auto x : adj[u]) {//todo na bumajke
            // time+=crossroads;
            time = tmp;
            Crossroads crossU = crossroads[u];
            long long weight = x.second;
            int v = x.first;
            Crossroads crossV = crossroads[v];
            if (vis[v] == false) {
                crossV = getCurrentCr(crossV, time);
                crossU = getCurrentCr(crossU, time);
                if (crossU.color == crossV.color) {
                    time += weight;
                    if ((dist[v] > dist[u] + weight)) {
                        path[v] = u;
                        if (dist[v] != LLONG_MAX)
                            pq.erase(pq.find(make_pair(dist[v], v)));

                        dist[v] = dist[u] + weight;
                        pq.insert(make_pair(dist[v], v));
                    }
                }
                else {

                    time = (ch(time, crossU, crossV));


                    time += weight;
                    if ((dist[v] > dist[u] + time)) {
                        path[v] = u;
                        if (dist[v] != LLONG_MAX)
                            pq.erase(pq.find(make_pair(dist[v], v)));

                        dist[v] = dist[u] + time;

                        pq.insert(make_pair(dist[v], v));
                    }

                }


            }
        }
    }


    return dist[last];
}

void printPath(int j) {

    // Base Case : If j is source
    if (path[j] == -1)
        return;

    printPath(path[j]);

    cout << " " << j;
}

int main() {
    freopen("lights.inp", "r", stdin);
    freopen("lights.out", "w", stdout);
    int first, last;
    //  int n, m;
    char color;
    bool bColor = false;
    int tiB, tiP, ric;
    cin >> first >> last >> n >> m;
    vector<Crossroads> crossroads(n + 1);
    path.resize(n + 1, -1);
    vector<vector<pair<int, int>>> adj(m);
    for (int i = 0; i < n; ++i) {
        cin >> color;
        switch (color) {
            case 'P':
                bColor = true;
                break;
            case 'B':
                bColor = false;
                break;
            default:
                break;
        }
        cin >> ric >> tiB >> tiP;
        crossroads[i + 1] = Crossroads(bColor, tiB, tiP, ric);
    }
    int i, j, kij;
    vis.resize(n + 1, false);
    for (int x = 0; x < m; ++x) {
        cin >> i >> j >> kij;
        adj[i].emplace_back(make_pair(j, kij));
        adj[j].emplace_back(make_pair(i, kij));
    }

    long long ans = shortestPath(adj, crossroads, last, first);
    if (ans != -1) {
        cout << ans << endl;
        cout << first;
        printPath(last);
    }
    else {
        cout << 0;
    }
    path.clear();
    adj.clear();
    return 0;
}