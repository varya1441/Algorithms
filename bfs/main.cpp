#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int n,m;


int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    in >> m >> n;
    int x;
    vector<vector<int >> vec(m+1, vector<int>(n+1, 0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> x;
            vec[i][j] = x;
        }
    }
    int counter=0;
    vector<vector<bool>> visited(m+1, vector<bool>(n+1, false));
    queue<pair<int, int>> pai;


    //int couner = 0;
    int i,j;
    for (int k = 0; k < n; ++k) {
        for (int t = 0; t < m; ++t) {
            if (vec[t][k] == 0 && visited[t][k] == false) {
                visited[t][k] = true;
                counter++;
                pai.push(make_pair(t, k));
                while (!pai.empty()) {
                    i=pai.front().first;
                    j=pai.front().second;
                    pai.pop();
                    if (j == n - 1) {

                    } else {
                        if (vec[i][j + 1] == 0 && (visited[i][j + 1] == false)) {
                            visited[i][j + 1] = true;
                            pai.push(make_pair(i, j + 1));
                        }
                    }
                    if ((i) != (m - 1)) {
                        if (vec[i + 1][j] == 0 && (visited[i + 1][j] == false)) {
                            visited[i + 1][j] = true;
                            pai.push(make_pair(i + 1, j));
                        }
                    } else {
                        if (vec[0][j] == 0 && (visited[0][j] == false)) {
                            visited[0][j] = true;
                            pai.push(make_pair(0, j));
                        }
                    }
                        if (i != 0) {
                            if (vec[i - 1][j] == 0 && (visited[i - 1][j] == false)) {
                                visited[i - 1][j] = true;
                                pai.push(make_pair(i - 1, j));
                            }
                        } else{
                            if (vec[m-1][j] == 0 && (visited[m-1][j] == false)) {
                                visited[m-1][j] = true;
                                pai.push(make_pair(m-1, j));
                            }
                        }
                        if (j != 0) {
                            if (vec[i][j - 1] == 0 && (visited[i][j - 1] == false)) {
                                visited[i][j - 1] = true;
                                pai.push(make_pair(i, j - 1));
                            }
                        } else {
//                       if ( (vec[i][n] == 0 )&& (visited[i][n] == false)) {
//                           visited[i][n] = true;
//                           pai.push(make_pair(i, n));
//                       }
                        }
                    //}
                }

            }

        }


    }
    out << counter;
}