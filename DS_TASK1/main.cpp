#include <stdio.h>

#include<iostream>
#include<numeric>
#include<algorithm>
#include<vector>

using namespace std;


long max_x = -1;

vector<long>t;
vector<long>lvls;

int sum( long l, long r) {
    int res = 0;

    // loop to find the sum in the range
    for (l += max_x, r += max_x; l < r; l >>= 1, r >>= 1)
    {
        if (l & 1)
            res += t[l++];

        if (r & 1)
            res += t[--r];
    }

    return res;
}
void upd(long x) {
    // set value at position p
    t[x + max_x]++;
    x = x + max_x;

    // move upward and update parents
    for (int i = x; i > 1; i >>= 1)
        t[i >> 1] = t[i] + t[i ^ 1];
}
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);


    long n;
    cin >> n;
    int x, y;

    vector<long>p;
    for (int i = 0; i < n; i++)
    {
        cin >> x >> y;
        if (max_x < x) {
            max_x = x;
        }
        p.push_back(x);

    }
  //  max_x += 228;
    t.resize(4e6, 0);
    lvls.resize(n, 0);
    int s,prevx,ylvl;
    prevx = (*p.begin());

    for(auto i = p.begin(); i != p.end();i++)
    {


        s = sum(prevx, (*i)+1);
        lvls[s]++;

        upd((*i));

    }
    for (int i = 0; i < n; i++)
    {
        cout << lvls[i] << endl;
    }


    return 0;
}
