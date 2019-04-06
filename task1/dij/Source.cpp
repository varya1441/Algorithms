#pragma warning(disable : 4996)
#include <vector>
#include <cstdio>
#include <functional>
#include <queue>
#include <iostream>

using namespace std;
vector<vector<pair<int, int> >> adj;
void shortestPath( int last, int first)
{

	priority_queue< pair<int, int>, vector< pair<int, int>>, greater<pair<int, int>> > pq;


	vector<int> dist(last,	INT_MAX);


	pq.push(make_pair(0, first));

	dist[first] = 0;


	while (!pq.empty())
	{

		int u = pq.top().second;
		pq.pop();

		for (auto x : adj[u])
		{
			int weight = x.second;
			int v = x.first;



			if (dist[v] > dist[u] + weight)
			{

				dist[v] = dist[u] + weight;
				pq.push(make_pair(dist[v], v));
			}
		}
	}


	cout << dist[last - 1];
}

int main()

{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n, first = 1, m;
	cin >> n >> m;
	int x, y, v;
	/*if (m == 0) {
		cout << 0;
		return 0;

	}*/
	adj.resize(n+1,vector<pair<int, int>>());
	for (int i = 0; i <m; ++i) {
		cin >> x >> y >> v;
		adj[x].emplace_back(y, v);
		adj[y].emplace_back(x, v);

	}
	shortestPath( n+1, first);

	return 0;
}