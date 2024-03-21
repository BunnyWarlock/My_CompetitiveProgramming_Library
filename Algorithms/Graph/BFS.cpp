// Author: Sahil Yasar
// Tested here:
// https://codeforces.com/edu/course/2/lesson/6/3/practice/contest/285083/problem/D

#include <iostream>
#include <vector>
#include <bitset>
#include <queue>
using namespace std;
#define endl '\n'

const int MAX = 1e5 + 10;
vector<pair<int, int>> g[MAX];
int lvl[MAX], pre[MAX];
bitset<MAX> vis;
int n, m, d;

// Remove lim to get normal bfs
void bfs(int s, int lim){
  queue<int> q;
  q.push(s);
  vis.reset();
  vis[s] = true;
  lvl[s] = pre[s] = 0;
  while(!q.empty()){
    s = q.front();
    q.pop();
    for (auto [x, w]: g[s])
      if (!vis[x] && w <= lim){
        q.push(x);
        pre[x] = s;
        vis[x] = true;
        lvl[x] = lvl[s]+1;
      }
  }
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin.exceptions(cin.failbit);

  int i, l, r, mid, ans, u, v, w;
  cin>>n>>m>>d;
  l = r = 0;
  for (i = 0; i < m; ++i){
    cin>>u>>v>>w;
    g[u].push_back({v, w});
    r = max(r, w);
  }

  auto check = [&](int mx){
    bfs(1, mx);
    return vis[n] && lvl[n] <= d;
  };

  ans = -1;
  while(l <= r){
    mid = (l+r)/2;
    if (check(mid)){
      ans = mid;
      r = mid-1;
    }
    else
      l = mid+1;
  }

  if (ans == -1)
    cout<<-1<<endl;
  else{
    vector<int> path;
    bfs(1, ans);
    while(n){
      path.push_back(n);
      n = pre[n];
    }

    cout<<path.size()-1<<endl;
    for (i = path.size()-1; i >= 0; --i)
      cout<<path[i]<<" ";
    cout<<endl;
  }

  return 0;
}
