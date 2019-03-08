#pragma warning(disable : 4996)
#include <stdio.h>

#include<iostream>
#include<numeric>
#include<cmath>
#include<algorithm>

using namespace std;
//int **dp;
//int *arr1, *arr2;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);


	int elem = 0, mini = 0;
	int size;
	int index = 0;
	cin >> size;

	int *arr = new int[size+1];
	while (elem <size) {
		cin >> index;

		arr[elem++] = index;
		cin >> index;
		if (elem == size) {
			arr[elem] = index;
		}
		

	}

	long long **dp = new long long*[size + 1];
	for (int i = 0; i <=size; i++) {
		dp[i] = new long long[size + 1];
		dp[i][i] = 0;

	}
	long long rem;
	int j = 0;
	for (int p = 1; p <= size; p++) {
		for (int i = 1; i <= size - p; i++) {
			j = i + p;

			dp[i][j] = INT32_MAX;
			for (int k = i; k <= j - 1; k++)
			{
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j]);

			}
	
		}
	}
	cout << dp[1][size];
	return 0;
}