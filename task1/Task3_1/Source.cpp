
/* C++ program to implement 2D Binary Indexed Tree

2D bit is basically a bit where each element is another bit.
Updating by adding v on (x, y) means it's effect will be found
throughout the rectangle [(x, y), (max_x, max_y)],
and query for (x, y) gives you the result of the rectangle
[(0, 0), (x, y)], assuming the total rectangle is
[(0, 0), (max_x, max_y)]. So when you query and update on
this bit,you have to be careful about how many times you are
subtracting a rectangle and adding it. Simple set union formula
works here.

So if you want to get the result of a specific rectangle
[(x1, y1), (x2, y2)], the following steps are necessary:

Query(x1,y1,x2,y2) = getSum(x2, y2)-getSum(x2, y1-1) -
getSum(x1-1, y2)+getSum(x1-1, y1-1)

Here 'Query(x1,y1,x2,y2)' means the sum of elements enclosed
in the rectangle with bottom-left corner's co-ordinates
(x1, y1) and top-right corner's co-ordinates - (x2, y2)

Constraints -> x1<=x2 and y1<=y2

/\
y  |
|           --------(x2,y2)
|          |       |
|          |       |
|          |       |
|          ---------
|       (x1,y1)
|
|___________________________
(0, 0)                   x-->

In this progrm we have assumed a square matrix. The
program can be easily extended to a rectangular one. */

#pragma warning(disable : 4996)
#include <stdio.h>

#include<iostream>
#include<numeric>
#include<algorithm>
#include<vector>

using namespace std;

// N-->max_x and max_y 
int max_x = INT_MIN;
int max_y = INT_MIN;
int size = 0;
vector<vector<int>> bit;
struct yCoordinate {
	yCoordinate *left, *right;
	int sum;
	yCoordinate() :left(NULL), right(NULL), sum(0) {}
};
struct xCoordinate
{
	xCoordinate *left, *right;
	yCoordinate *y;
	xCoordinate():left(NULL), right(NULL), y(NULL) {}

};
int getSum(yCoordinate* y) {
	if (y == NULL)return 0;
	return y->sum;
}
int ySum(yCoordinate*y,int tyl,int tyr,int yl,int yr) {
	if (yl > yr) {
		return 0;
	}
	if (yl == tyl && tyr == yr) {
		return getSum(y);
	}
	int tym = (tyl + tyr) / 2;
	//sum_y (vx, vy*2, tly, tmy, yl, min(yr,tmy))
	//+sum_y(vx, vy * 2 + 1, tmy + 1, try_, max(yl, tmy + 1), yr);
	return (y->left==NULL) ? 0 : ySum(y->left, tyl, tym, yl, min(yr, tym)) +
		(y->right==NULL) ? 0 : ySum(y->right, tym+1, tyr, max(yr, tym+1), yr) ;

}
int xSum(xCoordinate*x, int txl, int txr, int xl, int xr,int yl,int yr) {
	if (xl > xr) {
		return 0;
	}
	if (xl == txl && txr == xr) {
		return (x->y==NULL)?0: ySum(x->y,0,max_x-1,yl,yr);
	}
	int txm = (txl + txr) >>1;
	//sum_y (vx, vy*2, tly, tmy, yl, min(yr,tmy))
	//+sum_y(vx, vy * 2 + 1, tmy + 1, try_, max(yl, tmy + 1), yr);
	return ((x->left == NULL) ? 0 : xSum(x->left, txl, txm, xl, min(xr, txm),yl,yr) +
		(x->right == NULL) ? 0 : xSum(x->right,  txm+1, txr, max(xr, txm+1), xr, yl, yr));

}
void update_y(yCoordinate* yNode, int l, int r, int L, int R, int x, int y, int val) {
	if (L == R) {
		yNode->sum += val;
	}
	else {
		int m = (L + R) >> 1;
		if (y <= m) {
			if (yNode->left == NULL) yNode->left = new yCoordinate();
			update_y(yNode->left, l, r, L, m, x, y, val);
		}
		else {
			if (yNode->right == NULL) yNode->right = new yCoordinate();
			update_y(yNode->right, l, r, m + 1, R, x, y, val);
		}

		yNode->sum = getSum(yNode->right) + getSum(yNode->left);
	}
}

void update_x(xCoordinate* xNode, int L, int R, int x, int y, int val) {
	if (L != R) {
		int m = (L + R) >> 1;
		if (x <= m) {
			if (xNode->left == NULL) xNode->left = new xCoordinate();
			update_x(xNode->left, L, m, x, y, val);
		}
		else {
			if (xNode->right == NULL) xNode->right = new xCoordinate();
			update_x(xNode->right, m + 1, R, x, y, val);
		}
	}

	if (xNode->y == NULL) xNode->y = new yCoordinate();
	update_y(xNode->y, L, R, 0, max_x - 1, x, y, val);
}
// A structure to hold the queries 
//class Query
//{
// public:
//	int x; // x and y co-ordinates of bottom left 
//	int y; // x and y co-ordinates of top right 
//	Query() {
//		this->x =0;
//		this->y = 0;
//	}
// public:	Query(int x, int y) {
//		this->x = x;
//		this->y = y;
//	}
//
//};
//
//
//// A function to update the 2D bit 
//void updateBIT(int x, int y)
//{
//	for (int i = x; i <max_x; i = (i | (i + 1)))
//		for (int j = y; j <max_y; j = (j | (j + 1)))
//			bit[i][j] += 1;
//	//return;
//}
//
//// A function to get sum from (0, 0) to (x, y) 
//void getSum(int x, int y)
//{
//	int sum = 0;
//
//	for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
//		for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
//			sum += bit[i][j];
//	
//	cout<<(sum)<<endl;
//}
////int sum(int x, int y)
////{
////	int result = 0;
////	for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
////		for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
////			result += bit[i][j];
////	return result;
////}
//
//
//// A function to construct a 2D bit 
//
//
//// A function to answer the queries 
//void answerQueries(vector<Query> q, int size)
//{
//
//	for (int i = 0; i < size; i++)
//	{
//		int x = q[i].x;
//		int y = q[i].y;
//
//
//		 getSum(x, y);
//
//	}
//	
//}

// Driver program 
int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	
	int size;
	cin >> size;
	int x, y;
	//vector<Query>vec;
	xCoordinate* xC = new xCoordinate();
	vector<pair<int,int>>p;
	for (int i = 0; i < size; i++)
	{
		cin >> x >> y;
		if (max_x < x) {
			max_x = x;
			//size = max_x;
		}
		p.push_back(pair<int,int>(x,y));
		update_x(xC,0,size,x,y,1);//xren
		//vec.emplace(vec.begin() + i, x, y);
	
		
		
		
	}
	//bit.resize(max_x + 1, vector<int>(max_y + 1, 0));
	for (int i = 0; i < size; i++)
	{
		cout << xSum(xC,0,max_x,0,p[i].first,0,p[i].second);
	}
	//answerQueries(vec, size);

	return 0;
}
