#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;


const int INF = 1000000000;
int amount,n, x, y,m;
vector<int> sel ;

double  res = INF;
struct ver{
    int num;
    bool isUsed;
};
vector<pair<long,long>> vector1;
void cal(vector<vector<double>> arr){
    for (int j = 0; j <m ; ++j) {

    }

    for (int vertex= 0 ; vertex<n; vertex++) {
        vector<bool> used (n);
        vector<int> sel_e ;
        int v = vertex;
        int k;
        double minimum = 0;
        for (int i = 0; i < n; ++i) {
            if (i == n - 1) {
                used[vertex] = false;
            }
            double min = INF;
            used[v] = true;
            for (int to = 0; to < n; ++to)
                if (!used[to] && arr[v][to] < min) {
                    min = arr[v][to];
                    k = to;
                }
            sel_e.push_back(k);
            minimum += min;
            v = k;
        }

        if (res> minimum) {
            res = minimum;
            sel = sel_e;
        }
    }
}

double dist(pair<double,double> x,pair<double,double> y){
    return sqrt((x.first- y.first) *(x.first - y.first) + (x.second- y.second) * (x.second - y.second));
}

pair<double,int> ekon[20000];
bool mask[20000];
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin>>amount>>m;
    n=amount;
    while (amount != 0) {
       cin>>x>>y;
        vector1.emplace_back(make_pair(x , y));

        amount--;
    }

    vector<vector<double >>arr(n,vector<double >(n,0));

    for (int i = 0 ; i< n;i++)
    {
        for (int j = 0 ; j < n;j++)
        {
            if ( i!=j)
                arr[i][j]=sqrt((vector1[i].first- vector1[j].first) *(vector1[i].first - vector1[j].first) + (vector1[i].second- vector1[j].second) * (vector1[i].second - vector1[j].second));
        }
    }

    cal(arr);

    for(int i=0;i<n;i++){
        int r=(i+1)%n;
        int l=(i-1+n)%n;
        ekon[i].first = -dist(vector1[sel[i]],vector1[sel[l]])-dist(vector1[sel[i]],vector1[sel[r]])+dist(vector1[sel[l]],vector1[sel[r]]);
        ekon[i].second = i;
    }
    sort(ekon,ekon+n);

    for(int i=0;i<m-1;i++){
        mask[ekon[i].second]=1;
     //   res+=ekon[i].first;
    }
    res=0;
    vector<int> ress;
    for(int i=0;i<n;i++){
        if(!mask[i]) ress.push_back(sel[i]);
    }
    int h=ress.size();
    for(int i=0;i<h;i++) {
        res += dist(vector1[ress[i]], vector1[ress[(i + 1) % h]]);
    }


    printf("%.3f\n", res);
    cout<<n-m+1<<" ";
    for (int i = 0; i < ress.size() ; i ++)
    {
        cout<<ress[i]+1<<" ";
    }
    cout <<ress[0]+1<<'\n';
    for(int i=0;i<n;i++){
        if(mask[i]){
            cout<<"1 "<<sel[i]+1<<" "<<sel[i]+1<<'\n';
        }
    }
    return 0;
}