#include <fstream>
#include <vector>

using namespace std;

int n,m;


int main()
{
    ifstream in("in.txt");
    ofstream out("out.txt");
    in >> m>>n;
    int x;
    vector<vector<bool >>vec(m+1,vector<bool>(n+1,0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j <n ; ++j) {
                in>>x;
                vec[i][j]=x;
        }
    }
    int counter;
    vector<bool>cnt(n+1, false);
    bool line;
    for (int k = 0; k <n; ++k) {
        line =false;
        for (int i = 0; i <m ; ++i) {
            if(vec[i][k]==1){
                line=true;
            } else{
                break;
            }
        }
        if(line==true){
            cnt[k]=1;
        }
    }
    int c=0;
    for (int l = 0; l <n; ++l) {
        if(cnt[l]==1)
            c++;
    }
    out<<c;

}