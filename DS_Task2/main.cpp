
#include <vector>
#include <cstdio>
#include <functional>
#include <queue>
#include <iostream>

using namespace std;

int n, r, left, right;

struct V {
   // int weight;
    int parent;
    int priority;
    int rout;

    V(int parent, int priority, int rout) :  parent(parent), priority(priority),
                                                        rout(rout) {}
};

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    priority_queue<V>pq1;
    priority_queue<V>pq2;
    int first,last,n,r,versh=0,par=0;
    int c;
    cin>>n>>r>>last>>first;

    for (int i = 0; i <r ; ++i) {
        cin>>c;
        if(i>0){

        }
        for (int j = 0; j <c ; ++j) {

        }
        
    }


    return 0;
}