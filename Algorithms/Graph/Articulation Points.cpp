// Author: Sahil Yasar
// Description: Tarjan's Algorithm to find Articulation points
// Tested here:
// https://lightoj.com/problem/ant-hills

#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
#define endl '\n'

const int MAX = 1e4 + 10;
vector<int> g[MAX];
int timer, tin[MAX], low[MAX];
bitset<MAX> AP; // Articulation points
void dfsAP(int u, int p = -1){
    int children = 0;
    low[u] = tin[u] = ++timer;
    for (int& v: g[u]){
        if (!tin[v]){
            ++children;
            dfsAP(v, u);
            AP[u] = (AP[u] || tin[u] <= low[v]);
            low[u] = min(low[u], low[v]);
        }
        else if (v != p)
            low[u] = min(low[u], tin[v]);
    }
    if (p == -1) AP[u] = (children > 1);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t, n, m, i, a, b, loop = 1;
    cin>>t;
    while(t--){
        cin>>n>>m;
        for (i = 1; i <= n; ++i){
            g[i].clear();
            tin[i] = 0;
        }
        for (i = 0; i < m; ++i){
            cin>>a>>b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        timer = 0;
        AP.reset();
        dfsAP(1);
        cout<<"Case "<<(loop++)<<": "<<AP.count()<<endl;
    }

    return 0;
}
