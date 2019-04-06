#include <iostream>

#include<vector>

using namespace std;
int m, n,u,v;



struct V{

    vector<int>neighbors;
    int getSize(){
        return neighbors.size();
    }
    void toString(){
        int n=neighbors.size();
        for (int i = 0; i <n ; ++i) {
            cout<<neighbors[i]<<" ";
        }
    }


};
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> n >> m;
    vector<V>vec(n+1);

    int x,y;
    for (int i = 0; i <m ; ++i) {
        cin>>x>>y;
        vec[x].neighbors.emplace_back(y);
        vec[y].neighbors.emplace_back(x);
    }
    for (int i = 1; i <=n ; ++i) {
        cout<<vec[i].getSize()<<" ";
        vec[i].toString();
        cout<<endl;
    }


    return 0;
}