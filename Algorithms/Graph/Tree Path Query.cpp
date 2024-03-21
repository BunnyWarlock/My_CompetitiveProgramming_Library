// Author: Sahil Yasar
// Tested here:
// https://toph.co/p/broken-roads-and-hearts
// Given a weighted tree :
// 1) Update the weight of an edge
// 2) Find the sum of weight in the shortest path from node a to b

#include <iostream>
#include <vector>
using namespace std;
#define endl '\n'

typedef long long ll;

namespace segmentTree{
    template <class T>
    struct SEGtree{
        vector<T> arr;
        size_t N;
        T (*combine)(T, T);
        T temp;

        void build(T a[], int v, int tl, int tr){
            if (tl == tr){
                arr[v] = a[tl];
                return;
            }
            int tm = (tl + tr) / 2;
            build(a, v+1, tl, tm);
            build(a, v+2*(tm-tl+1), tm+1, tr);
            arr[v] = combine(arr[v+1], arr[v+2*(tm-tl+1)]);
        }
        SEGtree(T a[], int n, T (*f)(T, T), T val){
            N = n;
            arr.resize(2*N-1);
            combine = f;
            temp = val;
            build(a, 0, 0, N-1);
        }

        T query(int v, int tl, int tr, int l, int r){
            if (l > tr || r < tl)
                return temp;
            if (l <= tl && r >= tr)
                return arr[v];
            int tm = (tl + tr) / 2;
            return combine(query(v+1, tl, tm, l, r),
                   query(v+2*(tm-tl+1), tm+1, tr, l, r));
        }
        T query(int l, int r){
            return query(0, 0, N-1, l, r);
        }

        void update(int v, int tl, int tr, int pos, T val){
            if (tl == tr){
                arr[v] = val;
                return;
            }
            int tm = (tl + tr) / 2;
            if (pos <= tm) update(v+1, tl, tm, pos, val);
            else update(v+2*(tm-tl+1), tm+1, tr, pos, val);
            arr[v] = combine(arr[v+1], arr[v+2*(tm-tl+1)]);
        }
        void update(int pos, T val){
            update(0, 0, N-1, pos, val);
        }
    };
}
using namespace segmentTree;

const int MAX = 2e5 + 10;
const int LOG = 18;
vector<pair<int, int>> g[MAX];
int parent[MAX][LOG], depth[MAX], tin[MAX], tout[MAX], k, timer;
ll temp[MAX];

void dfs(int s, int p = 0, ll cost = 0, int d = 0){
  depth[s] = d;
  parent[s][0] = p;
  for (int i = 1; i < k; ++i)
    parent[s][i] = parent[parent[s][i-1]][i-1];

  temp[tin[s] = timer++] = cost;
  for (auto& [x, y]: g[s])
    if (x != p)
      dfs(x, s, y, d+1);
  temp[tout[s] = timer++] = -cost;
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

struct edge{
  int u, v;
};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin.exceptions(cin.failbit);

  ll n, i, q, t, a, b, val;
  cin>>n;
  k = 33 - __builtin_clz(n);
  timer = 0;

  edge e[n-1];
  for (i = 0; i < n-1; ++i){
    cin>>e[i].u>>e[i].v>>a;
    g[e[i].u].push_back({e[i].v, a});
    g[e[i].v].push_back({e[i].u, a});
  }

  dfs(1);
  SEGtree<ll> st(temp, timer, [](ll a, ll b)->ll{ return a+b; }, 0);

  cin>>q;
  while(q--){
    cin>>t>>a>>b;
    if (t == 1){
      auto [u, v] = e[a-1];
      if (depth[v] > depth[u])
        swap(u, v);
      st.update(tin[u], b);
      st.update(tout[u], -b);
    }
    else{
      val = lca(a, b);
      a = tin[a], b = tin[b], val = tin[val];
      val = st.query(0, a) + st.query(0, b) - 2*st.query(0, val);
      cout<<val<<endl;
    }
  }

  return 0;
}
