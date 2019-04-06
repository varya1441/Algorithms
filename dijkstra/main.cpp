
#include <vector>
#include <cstdio>
#include <functional>
#include <queue>
#include <iostream>

using namespace std;

void shortestPath(vector<pair<int,int> > adj[], int last, int first)
{

    priority_queue< pair<int, int>, vector< pair<int, int>> , greater<pair<int, int>> > pq;


    vector<int> dist(last, INT8_MAX);


    pq.push(make_pair(0, first));
    dist[first] = 0;


    while (!pq.empty())
    {

        int u = pq.top().second;
        pq.pop();

        for (auto x : adj[u])
        {

            int v = x.first;
            int weight = x.second;


            if (dist[v] > dist[u] + weight)
            {

                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }


        cout<<dist[last-1];
}

int main()

{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n,first=1,m;
    cin>>n>>m;
    int x,y,v;
    vector<vector<pair<int, int> >> adj[m];
    for (int i = 0; i <m ; ++i) {
        cin>>x>>y>>v;
        adj[x].push_back(make_pair(y, v));
        adj[y].push_back(make_pair(x, v));

    }


    shortestPath(adj, m, first);

    return 0;
}