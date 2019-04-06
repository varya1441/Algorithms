//#pragma warning(suppress : 4996)
#pragma warning(disable : 4996)
#include <stdio.h>
#include<set>
#include<iostream>
#include<numeric>

using namespace std;
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	set<long long int> numbers;
	long long int a=2;
	//cin >> a;
	while (!cin.eof()) {
		cin >> a;
		numbers.insert(a);	
		
	}
	long long int sum=accumulate(numbers.begin(), numbers.end(), 0);
	cout << sum;
	return 0;
}