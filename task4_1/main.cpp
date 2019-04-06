#include <iostream>

#include<vector>

using namespace std;
int m, n,u,v;

vector <vector<bool>>matrix;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> n >> m;
    matrix.resize(n+1,vector<bool>(n+1,0));
    for (int i = 0; i <m ; ++i) {
        cin>>u>>v;
        matrix[u][v]=1;
        matrix[v][u]=1;
    }
    for (int i = 1; i <=n; ++i) {
        for (int j = 1; j <=n ; ++j) {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}