#include <iostream>

#include<vector>

using namespace std;
int n;
vector<int> vec;

void read() {
    int x, y;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        vec[y] = x;

    }
}

void write() {
    for (int i = 1; i <= n; ++i) {

        cout << vec[i] << endl;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> n;

    vec.resize(n + 1, 0);

    read();
    write();

    return 0;
}