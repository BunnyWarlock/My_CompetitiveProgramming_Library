// Author: chilli
// Tested here:
// https://judge.yosupo.jp/problem/convolution_mod

#include <iostream>
#include <vector>
using namespace std;
#define endl '\n'

typedef long long ll;
ll powMod(ll x, ll p, ll m){
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

const ll mod = (119 << 23) + 1, root = 62; // = 998244353
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
typedef vector<ll> vl;
void ntt(vl& a) {
	int n = a.size(), L = 31 - __builtin_clz(n);
	static vl rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		ll z[] = {1, powMod(root, mod >> s, mod)};
		for (int i = k; i < 2*k; ++i) rt[i] = rt[i / 2] * z[i & 1] % mod;
	}
	vector<int> rev(n);
	for (int i = 0; i < n; ++i) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	for (int i = 0; i < n; ++i) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k)
            for (int j = 0; j < k; ++j){
			ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
			a[i + j + k] = ai - z + (z > ai ? mod : 0);
			ai += (ai + z >= mod ? z - mod : z);
		}
}

vl conv(const vl& a, const vl& b) {
	if (a.empty() || b.empty()) return {};
	int s = a.size() + b.size() - 1, B = 32 - __builtin_clz(s),
	    n = 1 << B;
	int inv = powMod(n, mod - 2, mod);
	vl L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	for (int i = 0; i < n; ++i)
		out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
	ntt(out);
	return {out.begin(), out.begin() + s};
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll n, m, i;
	cin>>n>>m;
	vl a(n), b(m);
	for (i = 0; i < n; ++i)
		cin>>a[i];
	for (i = 0; i < m; ++i)
		cin>>b[i];
	vl ans = conv(a, b);
	for (i = 0; i < ans.size(); ++i)
		cout<<ans[i]<<" ";
	cout<<endl;

    return 0;
}
