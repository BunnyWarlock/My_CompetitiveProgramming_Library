// Author: Sahil Yasar
// Description: Tarjan's Algorithm to find Articulation points and Bridges
// Tested here:
// https://lightoj.com/problem/ant-hills
// https://lightoj.com/problem/critical-links

#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <algorithm>
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

vector<pair<int, int>> BR; // Bridges
void dfsBR(int u, int p = -1){
    low[u] = tin[u] = ++timer;
    for (int& v: g[u]){
        if (!tin[v]){
            dfsBR(v, u);
            if (tin[u] < low[v])
                BR.emplace_back(min(u, v), max(u, v));
            low[u] = min(low[u], low[v]);
        }
        else if (v != p)
            low[u] = min(low[u], tin[v]);
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t, n, i, j, u, v, loop = 1;
    string s;
    cin>>t;
    while(t--){
        cin>>n;
        for (i = 0; i < n; ++i){
            g[i].clear();
            tin[i] = 0;
        }
        for (i = 0; i < n; ++i){
            cin>>u>>s;
            j = stoi(s.substr(1, s.size()-2));
            while(j--){
                cin>>v;
                g[u].push_back(v);
            }
        }

        timer = 0;
        // AP.reset();
        // dfsAP(1);
        // cout<<"Case "<<(loop++)<<": "<<AP.count()<<endl;
        BR.clear();
        for (i = 0; i < n; ++i)
            if (!tin[i])
                dfsBR(i);
        cout<<"Case "<<(loop++)<<": "<<endl;
        sort(BR.begin(), BR.end());
        cout<<BR.size()<<" critical links"<<endl;
        for (auto [u, v]: BR)
            cout<<u<<" - "<<v<<endl;
    }

    return 0;
}
