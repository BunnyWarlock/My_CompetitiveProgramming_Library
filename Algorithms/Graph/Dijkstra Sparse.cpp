// Author: Sahil Yasar
// Tested here:
// https://atcoder.jp/contests/abc340/tasks/abc340_d

#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
#include <algorithm>
using namespace std;
#define endl '\n'

vector<vector<pair<int, int>>> adj;

template <class T>
void dijkstra(int s, vector<T>& d, vector<int>& p) {
    d.assign(adj.size(), numeric_limits<T>::max());
    p.assign(adj.size(), -1);
    d[s] = 0;
    using P = pair<T, int>;
    priority_queue<P, vector<P>, greater<P>> q;
    q.push({0, s});
    while (!q.empty()) {
        auto [cost, now] = q.top();
        q.pop();
        if (cost != d[now]) continue;
        for (auto [to, len]: adj[now])
            if (d[now] + len < d[to]){
                d[to] = d[now] + len;
                p[to] = now;
                q.push({d[to], to});
            }
    }
}

vector<int> path(int s, int t, vector<int>& p) {
    vector<int> path;
    for (int v = t; v != s; v = p[v])
        path.push_back(v);
    path.push_back(s);
    reverse(path.begin(), path.end());
    return path;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    int64_t n, i, a, b, x;
    cin>>n;
    adj.resize(n);
    for (i = 0; i < n-1; ++i){
      cin>>a>>b>>x;
      adj[i].push_back({i+1, a});
      adj[i].push_back({--x, b});
    }

    vector<int64_t> d;
    vector<int> p;
    dijkstra(0, d, p);
    cout<<d[n-1]<<endl;

    // p = path(0, n-1, p);
    // for (auto& x: p)
    //   cout<<x<<"->";
    // cout<<"\b\b  "<<endl;

    return 0;
}
