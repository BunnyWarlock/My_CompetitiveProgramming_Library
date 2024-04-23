// Author: Sahil Yasar
// Tested here:
// https://codeforces.com/contest/1957/problem/C

#include <iostream>
using namespace std;
#define endl '\n'

typedef long long ll;
const int MOD = 1e9 + 7;
const int MAX = 3e5 + 10;
ll fac[MAX], ifac[MAX];

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

ll nCr(int n, int r){
    if (n < 0 || n < r || r < 0) return 0;
    return ((fac[n] * ifac[n-r]) % MOD * ifac[r]) % MOD;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll t, n, k, i, r, c, ans;

    ifac[0] = fac[0] = 1;
	for(int i = 1; i < MAX; i++)
        fac[i] = (fac[i - 1] * i) % MOD;
	ifac[MAX - 1] = powMod(fac[MAX - 1], MOD-2, MOD);
	for(int i = MAX - 2; i; i--)
        ifac[i] = (ifac[i + 1] * (i + 1)) % MOD;

    cin>>t;
    while(t--){
        cin>>n>>k;
        for (i = 0; i < k; ++i){
            cin>>r>>c;
            n -= 1 + (r != c);
        }

        ans = 0;
        for (i = n&1; i <= n; i += 2){
            ans += nCr(n, n-i) * ((fac[n-i]*ifac[(n-i)/2]) % MOD);
            ans %= MOD;
        }
        cout<<ans<<endl;
    }

    return 0;
}
