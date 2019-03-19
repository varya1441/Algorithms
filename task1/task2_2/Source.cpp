#pragma warning(disable : 4996)
#include <stdio.h>
 
#include<iostream>
#include<numeric>
#include<algorithm>
#include<vector>

using namespace std;

 int p, q;

long long dp[20][169][200][2];

int n, k;

long long count(int pos, int sum, int rem, int tight,
	int nonz, vector<int> num)
{
	if (pos == num.size()) {
		if (rem == 0 && sum<=q&&sum>=p)
		
			return 1;
		return 0;
	}

	if (dp[pos][sum][rem][tight] != -1)
		return dp[pos][sum][rem][tight];

	long long ans = 0;

	int limit = (tight ? 9 : num[pos]);

	for (int d = 0; d <= limit; d++) {

		int csum = sum + d;
		int crem = (rem * 10 + d) % k;
		int ctight = tight || (d < num[pos]);
		ans += count(pos + 1, csum, crem,
			ctight, nonz || d, num);
	}
	return dp[pos][sum][rem][tight] = ans;
}


long long solve(long long x)
{
	vector<int> num;
	while (x) {
		num.push_back(x % 10);
		x /= 10;
	}
	reverse(num.begin(), num.end());

	memset(dp, -1, sizeof(dp));
	return count(0, 0, 0, 0, 0, num);
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	long long a;
	long long b;
	
	cin >> k>>a>>b>>p>>q;
	if (a == b) {
		if ((a%k == 0))
		{
			cout << 1;
		}
		else
		{
			cout << 0;
		}
	}
	else
	{
		cout << solve(b) - solve(a - 1);
	}
	
	
	 return 0;
}

