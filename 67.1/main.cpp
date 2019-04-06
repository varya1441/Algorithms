#include <fstream>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int n, m;
queue<int> ver;
vector<bool> met;
vector<vector<bool>> vector1;
vector<int> path;

int curr = 0;
int verN = 0;

void BFS(int k) {
    if (met[k] == false) {
        ver.push(k);
        met[k] = true;

        path[k] = ++verN;
        while (!ver.empty()) {
            curr = ver.front();
            ver.pop();
            //cout << (curr + 1) << " ";
            for (int i = 0; i < n; i++) {
                if (met[(i)] == false && vector1[curr][i] == 1) {
                    ver.push(i);

                    met[i] = true;
                    path[i] = ++verN;


                }
            }
        }
    }
}

void print() {
    for (int t = 0; t < n; ++t) {
        cout << path[t] << " ";
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n;
    vector1.resize(n, vector<bool>(n, 0));
    met.resize(n, 0);
    path.resize(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> m;
            vector1[i][j] = m;
        }
    }


    for (int k = 0; k < n; ++k) {
        BFS(k);
    }
    print();

}



