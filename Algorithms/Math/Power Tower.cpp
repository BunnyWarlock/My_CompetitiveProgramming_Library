// Author: Sahil Yasar, Shahjalal Shohag
// Application of the generalized Euler Totient Function
// a^x = a^(MOD(x, phi(m))) % m
// MOD also accounts for when x < log2(m) < m as it leaves x unaffected
// The upperbound for the minimum number of iterations on the
// Euler Totient Function, phi(phi(...phi(n))) = 1, is ceil(log2(n))
// To get normal powMod just do qMod(x, p, MOD)%mod
// Tested here:
// https://codeforces.com/problemset/problem/906/D

#include <iostream>
#include <map>
using namespace std;
#define endl '\n'

typedef long long ll;
map<int, int> memo;
int phi(int n){
	if (memo.count(n))
		return memo[n];
    int e = n;
    for (ll i = 2; i*i <= n; ++i)
        if (n%i == 0){
            while(n%i == 0)
                n /= i;
            e -= e/i;
        }
    if (n > 1)
        e -= e/n;
    return memo[n] = e;
}

#define MOD(a,b) (a < b)? a: b+a%b
ll qMod(ll x, ll p, ll m){
    ll ans = 1;
    while(p){
        if (p&1)
            ans = MOD(ans*x, m);
        p = p>>1;
        x = MOD(x*x, m);
    }
    return ans;
}

const int MAX = 1e5 + 10;
int w[MAX];

ll solve(int l, int r, int mod){
	if (l == r || mod == 1) return MOD(w[l], mod);
	return qMod(w[l], solve(l+1, r, phi(mod)), mod);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

	int n, m, q, l, r, i;
	cin>>n>>m;
	for (i = 1; i <= n; ++i)
		cin>>w[i];
	cin>>q;
	while(q--){
		cin>>l>>r;
		cout<<solve(l, r, m)%m<<endl;
	}

    return 0;
}
