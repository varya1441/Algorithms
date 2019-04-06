

#pragma warning(disable : 4996)
#include <stdio.h>

#include<iostream>
#include<numeric>
#include<algorithm>
#include<vector>

using namespace std;


int max_x = -1;

vector<int>t;
vector<int>lvls;

int sum( int l, int r) {
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
void upd(int x) {
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

	
	int n;
	cin >> n;
	int x, y;
	
	vector<pair<int, int>>p;
	for (int i = 0; i < n; i++)
	{
		cin >> x >> y;
		if (max_x < x) {
			max_x = x;
		}
		p.push_back(pair<int, int>(x, y));

	}
	t.resize(max_x * 4, 0);
	lvls.resize(n, 0);
	int s,prevx,ylvl=1,curL=1;
	prevx = (*p.begin()).first+1;
	int prevy = (*p.begin()).second;
	upd((*p.begin()).first);
	for(auto i = p.begin()+1; i != p.end();i++)
	{
		
		if (prevy != (*i).second) {
			prevx = 0;
			prevy = (*i).second;
			ylvl = 0;
			
		}
		ylvl+= sum(prevx, (*i).first+1);
		prevx = (*i).first + 1;
		lvls[ylvl++]++;
		//y = (*i).second;
		upd((*i).first);
		/*for (int i = 0; i < length; i++)
		{

		}
		t[(*i).first]++;*/
	}
	for (int i = 0; i < n; i++)
	{
		cout << lvls[i] << endl;
	}
	//rect.resize(max_x * 4, vector<int>(max_x * 4, 0));


	return 0;
}
