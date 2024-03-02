// Author: Sahil Yasar
// Problem: https://bapsoj.org/contests/ncpc-preliminary-ju-2023/problems/E
// Not Tested!

#include <iostream>
#include <vector>
using namespace std;
#define endl '\n'

typedef long long ll;

const int MAX = 6e5;
const int LOG = 20;
vector<int> g[MAX];
int parent[MAX][LOG], maxA[MAX][LOG], k, depth[MAX];

void dfs(const int s, ll a[], ll ans[], int p = 0){
  parent[s][0] = p;
  for (int i = 1; i < k; ++i)
    parent[s][i] = parent[parent[s][i-1]][i-1];
  maxA[s][0] = a[s];
  for (int i = 1; i < k; ++i)
    maxA[s][i] = max(maxA[s][i-1], maxA[parent[s][i-1]][i-1]);

  int v = s;
  for (int i = k-1; i >= 0; --i)
    if (maxA[v][i] == a[s])
      v = parent[v][i];
  ans[s] = a[s]*(depth[s]-depth[v]) + ans[v];

  for (auto& x: g[s])
    if (x != p){
      depth[x] = depth[s]+1;
      dfs(x, a, ans, s);
    }
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin.exceptions(cin.failbit);

  ll t, n, u, v, i, loop = 1;
  cin>>t;
  while(t--){
    cin>>n;
    ll a[n+1], ans[n+1];
    for (i = 1; i <= n; ++i)
      cin>>a[i];
    k = 33 - __builtin_clz(n);
    ans[0] = 0;

    for (i = 1; i <= n; ++i)
      g[i].clear();
    depth[1] = 1;

    for (i = 1; i < n; ++i){
      cin>>u>>v;
      g[u].push_back(v);
      g[v].push_back(u);
    }

    dfs(1, a, ans);
    cout<<"Case "<<(loop++)<<":"<<endl;
    for (i = 1; i <= n; ++i)
      cout<<ans[i]<<" ";
    cout<<endl;
  }

  return 0;
}
