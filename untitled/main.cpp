#include <fstream>
#include <vector>

using namespace std;

long n,m;
long find(){
    vector<long> mector(m,1);
    vector<long>nector(m,1);

////////////дп вперед////////////////
    for (int j = 1; j <n; ++j) {
        for (int i = 0; i <m; ++i) {

            nector[i+1]=(nector[i]+mector[i+1])%1000000007;;

        }
        swap(nector,mector);
    }

    return mector[m-1];
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    in >> n>>m;
    out<<find();

}