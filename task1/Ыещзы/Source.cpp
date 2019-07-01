#pragma warning(disable : 4996)
#include <iostream>
#include <cstdio>
#include <queue>
#include <iostream>
#include <bitset>

using namespace std;

vector<vector<char>> used(0);
vector<int> mt;


short n, m;


void f(vector<vector<char>> g) {
	for (int i = 0; i < n; ++i) {

		for (int j = 0; j < m; ++j) {
			//  if (i == 0) {
			//if (g[i][j]) {
				//  if (j< m-1) {
				if (i < n - 1 && m > 1 && n > 1 && j < m - 1)
					g[i + 2][j + 1] = !g[i + 2][j + 1];

				if (i < n && m > 1 && n > 1 && j < m - 1) {
					g[i + 1][j + 2] = !g[i + 1][j + 2];
				}
				if (i > 0 && m > 1 && n > 1 && j < m - 1) {
					g[i - 1][j + 2] = !g[i - 1][j + 2];
				}
				if (n > 0 && j > 0 && i > 1) {
					g[i - 2][j - 1] = !g[i - 2][j - 1];
				}
				if (n > 0 && m > 0 && i > 2) {
					g[i - 2][j + 1] = !g[i - 2][j + 1];
				}
				if (i > 0 && j > 1) {
					g[i - 1][j - 2] = !g[i - 1][j - 2];
				}
				if (i > 0 && j > 1 && j < m && i < n) {
					g[i + 1][j - 2] = !g[i + 1][j - 2];
				}
				if (i < n - 1 && j>0) {
					g[i + 2][j - 1] = !g[i + 2][j - 1];
				}
				//    }
				//}
			//}
		}

	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> m;
	short x, y;
	mt.assign(n, -1);
	vector<vector<char>> g(n + 1, vector<char>(m + 1, 0));
	while (cin >> x) {
		cin >> y;
		g[x][y] = false;
	}
	f(g);
	cout << "u";
	return 0;
}