// Author: Sahil Yasar
// Tested here:
// https://www.spoj.com/problems/LCA/

#include <iostream>
#include <vector>
using namespace std;
#define endl '\n'

typedef long long ll;

const int MAX = 1010;
const int LOG = 10;
vector<int> g[MAX];
int parent[MAX][LOG], depth[MAX], k;

void dfs(int s, int p = 0){
  parent[s][0] = p;
  for (int i = 1; i < k; ++i)
    parent[s][i] = parent[parent[s][i-1]][i-1];

  for (auto& x: g[s])
    if (x != p){
      depth[x] = depth[s]+1;
      dfs(x, s);
    }
}

int jump(int n, int x){
  for (int i = 0; i < k; ++i)
    if ((x>>i)&1) n = parent[n][i];
  return n;
}

int lca(int a, int b){
  if (depth[a] < depth[b]) swap(a, b);
	a = jump(a, depth[a] - depth[b]);
	if (a == b) return a;
  for (int i = k-1; i >= 0; --i){
    int c = parent[a][i], d = parent[b][i];
    if (c != d) a = c, b = d;
  }
  return parent[a][0];
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin.exceptions(cin.failbit);

  ll t, n, m, i, j, q, u, v, loop = 1;
  cin>>t;
  while(t--){
    cin>>n;
    k = 33 - __builtin_clz(n);
    depth[1] = 1;

    for (i = 1; i <= n; ++i)
      g[i].clear();
    for (i = 1; i <= n; ++i){
      cin>>m;
      for (j = 0; j < m; ++j){
        cin>>u;
        g[i].push_back(u);
        g[u].push_back(i);
      }
    }

    dfs(1);
    cout<<"Case "<<(loop++)<<":"<<endl;
    cin>>q;
    while(q--){
      cin>>u>>v;
      cout<<lca(u, v)<<endl;
    }
  }

  return 0;
}
