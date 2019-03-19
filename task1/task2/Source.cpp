#pragma warning(disable : 4996)
#include <stdio.h>

#include<iostream>
#include<numeric>
#include<algorithm>
#include<vector>

using namespace std;

typedef long long int type;
bool cmp(int a, int b) {
	return a > b;
}

int findMax(vector<int> arr,int size) {
	
	vector<int>dataV;
	vector<int>dataV2;
	vector<int>dataIndV(size);
	vector<int>dataIndV2(size+1);
	dataV.emplace(dataV.begin(), INT32_MIN);

	for (int i = 1; i < size; i++)
	{
		dataV.emplace(dataV.begin() + i, INT32_MAX);
	}

	dataV2.emplace(dataV2.begin(), INT32_MAX);
	for (int i = 1; i <size+1; i++)
	{
		dataV2.emplace(dataV2.begin() + i, INT32_MIN);
	}
	
	int j = 0;
	for (int i = 0; i <size; i++)
	{		
		j = int(lower_bound(dataV.begin(), dataV.end(), arr[i]) - dataV.begin());
		if (j == size) {
			return j;
		}
		if (dataV[j-1] < arr[i] && arr[i] < dataV[j])
		{	
			dataV[j] = arr[i];
		}
		
		
		dataIndV[i] = j;
	
	}
	int ind = 1;
	for (auto i = arr.rbegin(); i != arr.rend(); ++i) {
		j = int(lower_bound(dataV2.begin(), dataV2.end(), (*i),cmp) - dataV2.begin());
		if (dataV2[j - 1] > (*i) && (*i) > dataV2[j]) {
			dataV2[j] = (*i);
		}
		dataIndV2[size-ind++] = j;
	}
	vector<int> data(size+1);


	data[size-1] =  dataIndV2[size-1];

	for (int j = size - 2; j >= 1; j--) {
		data[j] = max(dataIndV2[j], data[j + 1]);
	}

	int sum = INT32_MIN;
	int ci = INT32_MIN;
	for (int i = 0; i < size ; i++) {

		if (sum < (dataIndV[i] + data[i + 1])) 
		{
			sum = dataIndV[i] + data[i + 1];

		}

		if (ci < (dataIndV[i] + dataIndV2[i + 1]))
		{
			ci = dataIndV[i] + dataIndV2[i + 1];

		}
		
		

	}
	cout << ci << endl;

	return sum;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n;
	cin >> n;
	vector<int>arr;
	int i = 0;

	int size = n;
	while (i<size)
	{
		cin >> n;
		arr.emplace(arr.begin() + i++, n);
		
	}
	cout<<findMax(arr,size);
	return 0;
}