#pragma warning(disable : 4996)
#include <stdio.h>

#include<iostream>
#include<numeric>
#include<algorithm>
#include<vector>
#include<map>

using namespace std;
long m, n, c, x;
//map<int,int>h;
vector <long>ht;
void f(long x) {
	int j = 0;
	int num;
	while (true) {
		num= ((x%m) + c * (j++)) % m;
		if (ht[num] == -1) {
			ht[num] = x;
			return;
		}
		if (ht[num] == x) {
			return;
		}
	}
	
	
}
int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	cin >> m >> c >> n;
	ht.resize(m, -1);
	for (long i = 0; i < n; i++)
	{
		cin >> x;
		f(x);
	}
	for (long i = 0; i < m; i++)
	{
		cout << ht[i]<<" ";

	}

	
	return 0;
}