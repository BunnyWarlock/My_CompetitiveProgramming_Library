// Author: Sahil Yasar
// Tested here:
// https://codeforces.com/contest/617/submission/246806995
// Learn More:
// https://codeforces.com/blog/entry/61203
// It is ideal for problems with n = 10^6 and q = 10^4

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;
#define endl '\n'

int64_t hilbertOrder(int x, int y, int pow = 21, int rotate = 0){
	if (pow == 0) return 0;
	int hpow = 1 << (pow-1);
	int seg = (x < hpow)? ((y < hpow)? 0: 3): ((y < hpow)? 1: 2);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = hilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2)? add: (subSquareSize-add-1);
	return ans;
}

int freq[1<<20], a[100010], k;
long long cur = 0;

void add(int i){
  cur += freq[a[i]^k];
  ++freq[a[i]];
}
void del(int i){
  --freq[a[i]];
  cur -= freq[a[i]^k];
}
long long calc(){
  return cur;
}

vector<long long> mo(vector<pair<int, int>> q){
  int l = 0, r = -1;
  vector<long long> o(q.size()), ans(q.size());
  auto f = [&](pair<int, int>& a)
      { return hilbertOrder(a.first, a.second); };
  iota(o.begin(), o.end(), 0);
  sort(o.begin(), o.end(), [&](int a, int b){ return f(q[a]) < f(q[b]); });
  for (auto& i: o){
    while(r < q[i].second) add(++r);
    while(l > q[i].first) add(--l);
    while(l < q[i].first) del(l++);
    while(r > q[i].second) del(r--);
    ans[i] = calc();
  }
  return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    int n, m, i, j;
    cin>>n>>m>>k;
    for (i = 1; i <= n; ++i){
      cin>>a[i];
      a[i] ^= a[i-1];
    }

    vector<pair<int, int>> q(m);
    for (i = 0; i < m; ++i){
      cin>>q[i].first>>q[i].second;
      --q[i].first;// --q[i].second;
    }

    vector<long long> ans = mo(q);
    for (i = 0; i < m; ++i)
      cout<<ans[i]<<endl;

    return 0;
}

