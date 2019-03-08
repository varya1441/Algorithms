#pragma warning(disable : 4996)
#include <stdio.h>

#include<iostream>
#include<numeric>

using namespace std;

bool isHeap(int* arr, int size)
{
	int j = 0;
	int n = size / 2;
	for (int i = 0; i < n-1; i++)
	{
		j = 2 * i + 1;
		if ((arr[i] > arr[j]) || (arr[i] > arr[j + 1])) {
			return false;
		}
	}
	if (arr[n-1] > arr[(n-1)*2+1])
		return false;
	return true;
}
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int a;
	int i = 0;
	int num;
	cin >> num;

	int* arr = new int[num];
	for (int j = 0; j < num;j++) {
		cin >> a;
		arr[j] = a;
	}
	if (isHeap(arr, num)) {
		cout << "Yes"<<endl;
	}
	else
	{
		cout << "No"<<endl;
	}
	return 0;
}