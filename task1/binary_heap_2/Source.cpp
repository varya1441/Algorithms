#pragma warning(disable : 4996)
#include <stdio.h>
#include<bitset>
#include<iostream>
#include<numeric>
const int MAX=64;
using namespace std;
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	long long num;
	cin >> num;
	if (num < 0) {
		cout << -1;
		return 0;
	}
	bitset<MAX> bs(num);
	
		for (int i = 0; i<bs.size(); ++i)
			if (bs.test(i)) {
				cout << i<<endl;
			}



	return 0;
}