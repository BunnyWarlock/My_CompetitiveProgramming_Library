// Tested here:
// https://codeforces.com/contest/221/submission/245484164

// #include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define endl '\n'

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template<class T>
// using oset = tree<T, null_type, less<T>, rb_tree_tag,
//              tree_order_statistics_node_update>;

template <class ...Args> auto &print(const Args &...args)
{ return ((cerr<<args<<", "), ...)<<"\b\b)"<<endl; }
#define watch(...) if(true){cerr<<"("#__VA_ARGS__") = ("; print(__VA_ARGS__);}
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define read(arr) for(auto& x: arr) cin>>x
#define write(arr) for(auto& x: arr) cout<<x<<" "; cout<<endl
#define mem(x, n) memset(x, n, sizeof(x))

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;

int cur, sqt, n;
struct query{
  int l, r, ind;
  bool operator<(query& a){
    return make_pair(l/sqt, r) < make_pair(a.l/sqt, a.r);
  }
};

void mo(int freq[], int val, int del){
  if (val > n) return;
  cur -= (freq[val] == val);
  freq[val] += del;
  cur += (freq[val] == val);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    int m, i, j;
    cin>>n>>m;
    sqt = sqrt(n);
    int a[n], freq[n+1];
    read(a);
    mem(freq, 0);

    query q[m];
    for (i = 0; i < m; ++i){
      cin>>q[i].l>>q[i].r;
      --q[i].l, --q[i].r;
      q[i].ind = i;
    }
    sort(q, q+m);

    int ans[m];
    i = 0, j = -1, cur = 0;
    for (auto& [l, r, ind]: q){
      while(j < r) mo(freq, a[++j], 1);
      while(i > l) mo(freq, a[--i], 1);

      while(i < l) mo(freq, a[i++], -1);
      while(j > r) mo(freq, a[j--], -1);

      ans[ind] = cur;
    }
    for (i = 0; i < m; ++i)
      cout<<ans[i]<<endl;

    return 0;
}
