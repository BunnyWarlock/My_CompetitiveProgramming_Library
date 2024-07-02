// Author: Lukas Polacek
// Modified by: Sahil Yasar
// Tested here:
// https://atcoder.jp/contests/abc221/tasks/abc221_e

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;
#define endl '\n'

namespace fenwickTree{
    template <class T>
	struct FT {
		vector<T> bit;
		T (*combine)(T, T);
		T temp;

		FT(int n, T (*f)(T, T), T val){
			bit.resize(n, val);
			combine = f;
            temp = val;
		}

		// a[pos] += dif
		void update(int pos, T dif) {
			for (; pos < bit.size(); pos |= pos + 1)
				bit[pos] = combine(bit[pos], dif);
		}

		// queires in [0, pos]
		T query(int pos) {
			T res = temp;
			for (++pos; pos > 0; pos &= pos - 1)
				res = combine(res, bit[pos-1]);
			return res;
		}

		// Only use if combine(a, b) is a+b
		// min pos such that sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if sum is empty.
		int lower_bound(T sum) {
			if (sum <= 0) return -1;
			int pos = 0;
			for (int pw = 1 << 25; pw; pw >>= 1)
				if (pos + pw <= bit.size() && bit[pos + pw-1] < sum)
					pos += pw, sum -= bit[pos-1];
			return pos;
		}
	};
}
using namespace fenwickTree;

typedef long long ll;
const ll MOD = 998244353;

ll modpow(ll x, ll p, ll m){
	ll ans = 1;
	x %= m;
	if (!x) return 0;
	while(p){
		if (p&1)
			ans = (ans*x)%m;
		p = p>>1;
		x = (x*x)%m;
	}
	return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

	ll n, i, ans, temp;
	cin>>n;
	ll a[n], ind[n];
	for (i = 0; i < n; ++i)
		cin>>a[i];

	FT<ll> s(n, [](ll a, ll b){ return (a+b)%MOD; }, 0LL);

	iota(ind, ind+n, 0);
	sort(ind, ind+n, [&](ll& x, ll& y){
		return make_pair(a[x], x) < make_pair(a[y], y);
	});

	ans = 0;
	temp = modpow(2, MOD-2, MOD);
	for (auto x: ind){
		i = s.query(x-1);
		ans = (ans + i*modpow(2, x, MOD)) % MOD;
		s.update(x, modpow(temp, x+1, MOD));
	}
	cout<<ans<<endl;

    return 0;
}
