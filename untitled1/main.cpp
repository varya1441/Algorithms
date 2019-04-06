#include <fstream>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int n, m;
queue<int> ver;
vector<bool> visited;
vector<vector<bool>> vector1;
//vector<int> path;
vector<int>met;
//int curr = 0;
//int verN = 0;
int time = 1;

void DFS(int k) {
//        time=1;
        visited[k] = true;

       // met[k] = ++time;

            for (int i = 0; i < n; i++) {
                if (visited[i] == false && vector1[k][i] == 1) {
                    time++;
                 DFS(i);


                }
            }
   // return time;

}

void print() {
    for (int t = 0; t < n; ++t) {
        cout << met[t] << " ";
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n;
    vector1.resize(n, vector<bool>(n, 0));
    visited.resize(n, false);
    met.resize(n,0);

    int counter=0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> m;
            vector1[i][j] = m;
            if(m==1){
                counter++;
            }
        }
    }

    if(counter/2!=n-1){
        cout<<"No";
        return 0;
    }
   // int t=0;
    for (int k = 0; k < n; ++k) {
        if(visited[k]==false) {
         //   time++;
            DFS(k);
        }
    }
    if(time!=n){
        cout<<"No";
        return 0;
    } else{
        cout<<"Yes";
        return 0;
    }




}