
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


int max_x = -1;
//int max_y = INT_MIN;
//int size=0;
vector<vector<int>>rect;

// size of x coordinate. 
int size = 4;

/*
* A recursive function that constructs
* Inital Segment Tree for array rect[][] = { }.
* 'pos' is index of current node in segment
* tree seg[]. 'strip' is the enumeration
* for the y-axis.
*/
int ini_seg[1000][1000] = { 0 }; 
  
// final 2d-segment tree. 
int fin_seg[1000][1000] = { 0 }; 
void segment(int low, int high,
	int pos, int strip)
{
	if (high == low) {
		ini_seg[strip][pos] = rect[strip][low];
	}
	else {
		int mid = (low + high) / 2;
		segment(low, mid, 2 * pos, strip);
		segment(mid + 1, high, 2 * pos + 1, strip);
		ini_seg[strip][pos] = ini_seg[strip][2 * pos] +
			ini_seg[strip][2 * pos + 1];
	}
}

/*
* A recursive function that constructs
* Final Segment Tree for array ini_seg[][] = { }.
*/
void finalSegment(int low, int high, int pos)
{
	if (high == low) {

		for (int i = 1; i < 2 * ::size; i++)
			fin_seg[pos][i] = ini_seg[low][i];
	}
	else {
		int mid = (low + high) / 2;
		finalSegment(low, mid, 2 * pos);
		finalSegment(mid + 1, high, 2 * pos + 1);

		for (int i = 1; i < 2 * ::size; i++)
			fin_seg[pos][i] = fin_seg[2 * pos][i] +
			fin_seg[2 * pos + 1][i];
	}
}

/*
* Return sum of elements in range from index
* x1 to x2 . It uses the final_seg[][] array
* created using finalsegment() function.
* 'pos' is index of current node in
* segment tree fin_seg[][].
*/
int finalQuery(int pos, int start, int end,
	int x1, int x2, int node)
{
	if (x2 < start || end < x1) {
		return 0;
	}

	if (x1 <= start && end <= x2) {
		return fin_seg[node][pos];
	}

	int mid = (start + end) / 2;
	int p1 = finalQuery(2 * pos, start, mid,
		x1, x2, node);

	int p2 = finalQuery(2 * pos + 1, mid + 1,
		end, x1, x2, node);

	return (p1 + p2);
}

/*
* This fuction calls the finalQuery fuction
* for elements in range from index x1 to x2 .
* This fuction queries the yth coordinate.
*/
int query(int pos, int start, int end,
	int y1, int y2, int x1, int x2)
{
	if (y2 < start || end < y1) {
		return 0;
	}

	if (y1 <= start && end <= y2) {
		return (finalQuery(1, 0, ::size-1, x1, x2, pos));
	}

	int mid = (start + end) / 2;
	int p1 = query(2 * pos, start,
		mid, y1, y2, x1, x2);
	int p2 = query(2 * pos + 1, mid + 1,
		end, y1, y2, x1, x2);

	return (p1 + p2);
}

/* A recursive function to update the nodes
which for the given index. The following
are parameters : pos --> index of current
node in segment tree fin_seg[][]. x ->
index of the element to be updated. val -->
Value to be change at node idx
*/
//int finalUpdate(int pos, int low, int high,
//	int x, int val, int node)
//{
//	if (low == high) {
//		fin_seg[node][pos] = val;
//	}
//	else {
//		int mid = (low + high) / 2;
//
//		if (low <= x && x <= mid) {
//			finalUpdate(2 * pos, low, mid, x, val, node);
//		}
//		else {
//			finalUpdate(2 * pos + 1, mid + 1, high,
//				x, val, node);
//		}
//
//		fin_seg[node][pos] = fin_seg[node][2 * pos] +
//			fin_seg[node][2 * pos + 1];
//	}
//}
//
///*
//This funtion call the final update function after
//visiting the yth coordinate in the segment tree fin_seg[][].
//*/
//int update(int pos, int low, int high, int x, int y, int val)
//{
//	if (low == high) {
//		finalUpdate(1, 1, 4, x, val, pos);
//	}
//	else {
//		int mid = (low + high) / 2;
//
//		if (low <= y && y <= mid) {
//			update(2 * pos, low, mid, x, y, val);
//		}
//		else {
//			update(2 * pos + 1, mid + 1, high, x, y, val);
//		}
//
//		for (int i = 1; i < size; i++)
//			fin_seg[pos][i] = fin_seg[2 * pos][i] +
//			fin_seg[2 * pos + 1][i];
//	}
//}

// Driver program to test above functions 


//struct yCoordinate {
//	yCoordinate *left, *right;
//	int sum;
//	yCoordinate() :left(NULL), right(NULL), sum(0) {}
//};
//struct xCoordinate
//{
//	xCoordinate *left, *right;
//	yCoordinate *y;
//	xCoordinate():left(NULL), right(NULL), y(NULL) {}
//
//};
//int getSum(yCoordinate* y) {
//	if (y == NULL)return 0;
//	return y->sum;
//}
//int ySum(yCoordinate*y,int tyl,int tyr,int yl,int yr) {
//	if (yl > yr) {
//		return 0;
//	}
//	if (yl == tyl && tyr == yr) {
//		return getSum(y);
//	}
//	int tym = (tyl + tyr) / 2;
//	//sum_y (vx, vy*2, tly, tmy, yl, min(yr,tmy))
//	//+sum_y(vx, vy * 2 + 1, tmy + 1, try_, max(yl, tmy + 1), yr);
//	int sum1 = (y->left ) ? ySum(y->left, tyl, tym, yl, min(yr, tym)):0;
//	int sum2 = (y->right ) ?  ySum(y->right, tym + 1, tyr, max(yl, tym + 1), yr):0;
//	return  sum1 + sum2;
//
//}
//int xSum(xCoordinate*x, int txl, int txr, int xl, int xr,int yl,int yr) {
//	if (xl > xr) {
//		return 0;
//	}
//	if (xl == txl && txr == xr) {
//		return (x->y)? ySum(x->y,0,::size,yl,yr):0;
//	}
//	int txm = (txl + txr)/2;
//	//sum_y (vx, vy*2, tly, tmy, yl, min(yr,tmy))
//	//+sum_y(vx, vy * 2 + 1, tmy + 1, try_, max(yl, tmy + 1), yr);
//	int sum1 = (x->left) ?  xSum(x->left, txl, txm, xl, min(xr, txm), yl, yr):0;
//	int sum2 = (x->right ) ? xSum(x->right, txm + 1, txr, max(xl, txm + 1), xr, yl, yr):0;
//	return  sum1+sum2;
//
//}
//void update_y(yCoordinate* yNode, int l, int r, int L, int R, int x, int y, int val) {
//	if (L == R) {
//		yNode->sum += val;
//	}
//	else {
//		int m = (L + R) >> 1;
//		if (y <= m) {
//			if (yNode->left == NULL) yNode->left = new yCoordinate();
//			update_y(yNode->left, l, r, L, m, x, y, val);
//		}
//		else {
//			if (yNode->right == NULL) yNode->right = new yCoordinate();
//			update_y(yNode->right, l, r, m + 1, R, x, y, val);
//		}
//
//		yNode->sum = getSum(yNode->right) + getSum(yNode->left);
//	}
//}
//
//void update_x(xCoordinate* xNode, int L, int R, int x, int y, int val) {
//	if (L != R) {
//		int m = (L + R) >> 1;
//		if (x <= m) {
//			if (xNode->left == NULL) xNode->left = new xCoordinate();
//			update_x(xNode->left, L, m, x, y, val);
//		}
//		else {
//			if (xNode->right == NULL) xNode->right = new xCoordinate();
//			update_x(xNode->right, m + 1, R, x, y, val);
//		}
//	}
//
//	if (xNode->y == NULL) xNode->y = new yCoordinate();
//	update_y(xNode->y, L, R, 0, ::size, x, y, val);
//}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	
	int n;
	cin >> n;
	::size = 0;
	int x, y;
	int pos = 1;
	int low = 0;
	int high = 3;
	
	vector<pair<int, int>>p;
	for (int i = 0; i < n; i++)
	{
		cin >> x >> y;
		if (max_x < x) {
			max_x = x;
		}
		p.push_back(pair<int, int>(x, y));
		//segment(1, ::size - 1, x, y);

		// Call the final function to built the 2d segment tree. 

		//xren

	}
	rect.resize(max_x * 4, vector<int>(max_x * 4, 0));
	::size = 4 * max_x;
	for (auto i = p.begin();i!=p.end(); i++)
	{
		segment(1, ::size - 1, (*i).first, (*i).second);

		// Call the final function to built the 2d segment tree. 

		//xren

	}

	finalSegment(1, ::size - 1, 0);
	// Call the ini_segment() to create the 
	// inital segment tree on x- coordinate 
//	for (int strip = 0; strip < n; strip++)
		

	/*
	Query:
	* To request the query for sub-rectangle y1, y2=(2, 3) x1, x2=(2, 3)
	* update the value of index (3, 3)=100;
	* To request the query for sub-rectangle y1, y2=(2, 3) x1, x2=(2, 3)
	*/
	cout << "The sum of the submatrix (y1, y2)->(2, 3), "
		<< " (x1, x2)->(2, 3) is "
		<< query(1, 0, ::size-1, 0, 2, 0, 5) << endl;

	// Function to update the value 
	//update(1, 1, 4, 2, 3, 100);
	//xCoordinate* xC = new xCoordinate();
	
	/*for (auto i = p.begin(); i !=p.end(); i++)
	{
		update_x(xC, 0, max_x, (*i).first, (*i).second, 1);
	}
	vector<int>vec(n);
	int num = 0;
	for (int i = 0; i < n; i++)
	{
		num =( xSum(xC, 0, max_x, 0, p[i].first, 0, p[i].second) - 1);
		vec[num] += 1;
	}
	for_each(vec.begin(), vec.end(), [](int v) {cout << v << endl; });*/
	

	return 0;
}
