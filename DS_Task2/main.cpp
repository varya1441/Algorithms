#include <vector>
#include <cstdio>
#include <queue>
#include <iostream>

using namespace std;

int_fast32_t n;

int_fast32_t last;
struct V;
struct Q;
int_fast32_t first;
vector<vector<V *>> adj;

struct V {
    int_fast32_t num;
    int_fast16_t priority;
    int_fast16_t rout;
    bool visited;


    V(int num, int_fast16_t priority, int_fast16_t rout, bool visited);

    V();

};

struct Q {
    V *current;
    Q *prev;
    int_fast32_t dist;

    Q();

    Q(V *current, Q *prev, int_fast32_t dist) : current(current), prev(prev), dist(dist) {}
};

Q::Q() {

}


V::V(int_fast32_t num, int_fast16_t priority, int_fast16_t rout, bool visited) : num(num), priority(priority), rout(rout), visited(visited) {}

V::V() = default;




queue<Q *> pq4;
queue<Q *> pq1;
V *_v = nullptr;
Q *u = nullptr;

int_fast32_t dijksta(int_fast32_t firstT, int_fast32_t last) {


    while (!pq1.empty() || !pq4.empty()) {

        if (!pq1.empty() && !pq4.empty()) {
            if (pq1.front()->dist < pq4.front()->dist) {
                u = pq1.front();
                pq1.pop();
            } else {
                u = pq4.front();
                pq4.pop();
            }
        } else if (!pq4.empty()) {
            u = pq4.front();
            pq4.pop();


        } else if (!pq1.empty()) {
            u = pq1.front();
            pq1.pop();


        }

        (_v) = (u->current);
        if ((u)->current->visited)continue;
        (u)->current->visited = true;
        if (((_v)->num) == last) {
            return u->dist;
        }
        for (V *x : adj[(_v)->num]) {
            if (!x->visited) {
                {


                    if (x->rout == (_v)->rout && (abs(x->priority - (_v)->priority) == 1)) {


                        pq1.emplace(new Q(x, u, u->dist + 1));


                    } else {

                        pq4.emplace(new Q(x, u, u->dist + 4));


                    }

                }
            }
        }


    }


    return -1;

}

void print() {
    Q *curr = u;
    while (curr != nullptr) {
        cout << curr->current->num << " " << curr->current->rout << endl;
        curr = (curr->prev);
    }


}


int main() {
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    //cout.tie(nullptr);

    int_fast16_t r, c;
    int_fast32_t _u, v;

    cin >> n >> r >> first >> last;

    if (first == last) {
        cout << 0;
        return 0;
    }
    adj.resize(static_cast<size_t>(n + 1), vector<V *>());
    for (int_fast16_t i = 0; i < r; ++i) {
        cin >> c;
        cin >> _u;
        V *ver1 = new V(_u, 0, i + 1, false);
        if (_u == first) {
            pq1.emplace(new Q(ver1, nullptr, 0));
        }
        for (int_fast16_t j = 0; j < c - 1; ++j) {
            cin >> v;
            V *ver2 = new V(v, j + 1, i + 1, false);

            if (v == first) {

                pq1.emplace(new Q(ver2, nullptr, 0));
            }

            adj[_u].emplace_back(ver2);
            adj[v].emplace_back(ver1);
            ver1 = ver2;
            _u = v;
        }

    }

    int_fast32_t ans = dijksta(first, last);
//    while (pq1.empty()){
//        pq1.pop();
//    }
//    while (pq4.empty()){
//        pq4.pop();
//    }
    if (ans != -1) {
        cout << ans << endl;
        print();

    } else {
        cout << "NoWay" << endl;
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}