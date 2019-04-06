#pragma warning(disable : 4996)
#include <stdio.h>
#include <algorithm>
#include<iostream>
#include<vector>


using namespace std;


int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int a;
	int i = 0;
	long num;
	cin >> num;

	vector<long> arr;
	for (int j = 0; j <num;j++) {
		cin >> a;
		arr.emplace(arr.begin()+j,a);
	}
	if (is_heap(arr.begin(), arr.end(), [](long a,long b) {return a>b; })) {
		cout << "Yes"<<endl;
	}
	else
	{
		cout << "No"<<endl;
	}
	return 0;
}