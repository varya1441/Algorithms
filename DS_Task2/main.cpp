#include <vector>
#include <cstdio>
#include <functional>
#include <queue>
#include <iostream>

using namespace std;

int n, r, left, right;
int last;
vector<bool> visited;
struct V;
int first;
vector<vector<V>> adj;

vector<pair<int, int>> path;

struct V {
    int num;
    int parent;
    int priority;
    int rout;

    V(int num, int parent, int priority, int rout);

    V();

};

V::V(int num, int parent, int priority, int rout) : num(num), parent(parent), priority(priority), rout(rout) {}

V::V() {}


struct cmp {
    bool operator()(const pair<long long, V> &rhs, const pair<long long, V> &rhs2) {
        return rhs.first > rhs2.first;
    }
};
priority_queue<pair<long long, V>, vector<pair<long long, V >>, cmp> pq4;
deque<pair<long long ,V>>dq;//
priority_queue<pair<long long, V>, vector<pair<long long, V >>, cmp> pq1;

int dijksta(int firstT, int last) {


    auto *dist = new long long[n + 1];
    for (int i = 0; i <= n; ++i) {
        dist[i] = LLONG_MAX;
    }



    dist[firstT] = 0;
    visited[firstT] = true;
    V v;
    pair<long long, V> u;

    while (!pq1.empty() || !pq4.empty()) {

        if (!pq1.empty() && !pq4.empty()) {
            if (pq1.top().first< pq4.top().first) {
                u = pq1.top();
                pq1.pop();
            } else {
                u = pq4.top();
                pq4.pop();
            }
        } else if (!pq4.empty()) {
            u = pq4.top();
            pq4.pop();


        } else if (!pq1.empty()) {
            u = pq1.top();
            pq1.pop();


        }

        v = u.second;
        for (auto x : adj[v.num]) {
           if (visited[x.num] == false) {
                {


                    if (x.rout != v.rout) {
                        if (dist[x.num] >= u.first + 4) {
                            dist[x.num] =  u.first + 4;

                            path[x.num] = make_pair(u.second.num, x.rout);
                            pq4.push(make_pair(dist[x.num], x));
                        }

                    } else {
                        if ((dist[x.num] >= u.first + 1)) {
                            dist[x.num] = u.first + 1;
                            path[x.num] = make_pair(u.second.num, v.rout);
                            pq1.push(make_pair(dist[x.num], x));
                        }
                    }

                    visited[u.second.num] = true;
                    if(v.num==last){
                        return dist[last];
                    }
                }
            }
        }


    }


    return dist[last];

}

void print(int last) {


    if (last == ::first ) {

        return;
    }



    print(path[last].first);

    cout << path[last].first << " " << path[last].second << endl;


}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);


    int u, v;
    int c;

    cin >> n >> r >> last >> first;
    if(first==last){
        cout<<0;
        return 0;
    }
    adj.resize(n + 1, vector<V>());
    path.resize(n + 1, make_pair(-1, -1));
    visited.resize(n + 1, false);
    for (int i = 0; i < r; ++i) {
        cin >> c;
        cin >> u;

        for (int j = 0; j < c - 1; ++j) {
            cin >> v;
            if(u==first){
                adj[u].push_back(V(v, u, j+1, i + 1));
                adj[v].push_back(V(u, v, j+1, i + 1));
                pq1.push(make_pair(0,V(u, v, j+1, i + 1)));
            }
            else
            {
                adj[u].push_back(V(v, u, j+1, i + 1));
                adj[v].push_back(V(u, v, j+1, i + 1));
            }


            u = v;
        }

    }
    long long ans = dijksta( first,last);
    if (ans != -1) {
        cout << ans << endl;
        print(last);
        cout<<last<<" "<<path[last].second;
    } else {
        cout << "NoWay" << endl;
    }
    return 0;
}