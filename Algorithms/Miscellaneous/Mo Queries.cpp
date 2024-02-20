// Author: Simon Lindholm
// Modified by: Sahil Yasar
// Tested here:
// https://codeforces.com/contest/221/submission/245621756

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;
#define endl '\n'

int freq[100010], a[100010], cur = 0;

void add(int i){
  int val = a[i];
  if (val >= 100010) return;
  cur -= (freq[val] == val);
  cur += (++freq[val] == val);
}
void del(int i){
  int val = a[i];
  if (val >= 100010) return;
  cur -= (freq[val] == val);
  cur += (--freq[val] == val);
}
int calc(){
  return cur;
}

vector<int> mo(vector<pair<int, int>> q){
  int l = 0, r = -1, blk = 350;
  vector<int> o(q.size()), ans(q.size());
  auto f = [&](pair<int, int>& a)
      { return make_pair(a.first/blk, a.second^(a.first/blk & 1)); };
  iota(o.begin(), o.end(), 0);
  sort(o.begin(), o.end(), [&](int a, int b){ return f(q[a]) < f(q[b]); });
  for (int& i: o){
    while(l < q[i].first) del(l++);
    while(r > q[i].second) del(r--);
    while(r < q[i].second) add(++r);
    while(l > q[i].first) add(--l);
    ans[i] = calc();
  }
  return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    int n, m, i, j;
    cin>>n>>m;;
    for (i = 0; i < n; ++i)
      cin>>a[i];

    vector<pair<int, int>> q(m);
    for (i = 0; i < m; ++i){
      cin>>q[i].first>>q[i].second;
      --q[i].first, --q[i].second;
    }

    vector<int> ans = mo(q);
    for (i = 0; i < m; ++i)
      cout<<ans[i]<<endl;

    return 0;
}
