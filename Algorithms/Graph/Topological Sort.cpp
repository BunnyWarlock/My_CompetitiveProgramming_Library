// Author: Sahil Yasar
// Tested here:
// https://www.spoj.com/problems/TOPOSORT/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'

const int MAX = 1e4 + 10;
vector<int> g[MAX];
vector<int> toposort(int n = MAX){
    vector<int> in(n, 0);
    for (int i = 0; i < n; ++i)
        for (auto to: g[i])
            ++in[to];
    // Problem Specific, Queue works fine
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 0; i < n; ++i)
        if (!in[i])
            q.push(i);
    vector<int> order;
    while(!q.empty()){
        int at = q.top();
        q.pop();
        order.push_back(at);
        for (auto to: g[at]){
            --in[to];
            if (!in[to])
                q.push(to);
        }
    }
    if (order.size() != n)
        return vector<int>();
    return order;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m, i, u, v;
    cin>>n>>m;
    for (i = 0; i < m; ++i){
        cin>>u>>v;
        --u, --v;
        g[u].push_back(v);
    }

    vector<int> ans = toposort(n);
    if (ans.empty())
        cout<<"Sandro fails."<<endl;
    else{
        for (auto x: ans)
            cout<<x+1<<" ";
        cout<<endl;
    }

    return 0;
}
