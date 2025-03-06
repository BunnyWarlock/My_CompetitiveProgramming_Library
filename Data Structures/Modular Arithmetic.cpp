// Author: Sahil Yasar
// Tested here:
// https://codeforces.com/contest/1957/problem/C
// https://cses.fi/problemset/task/2064

#include <iostream>
#include <assert.h>
using namespace std;
#define endl '\n'

namespace modInt{
    int64_t extgcd(int64_t a, int64_t b, int64_t& x, int64_t& y) {
        if (!b){ x = 1, y = 0; return a; }
        int64_t res = extgcd(b, a%b, y, x);
        y -= (a/b)*x;
        return res;
    }

    template <const int64_t MOD>
    struct mint{
        int64_t val;
        using Mint = mint<MOD>;
        mint(): val(0) {}
        mint(int64_t x) { val = ((x % MOD) + MOD) % MOD; }
        inline Mint operator=(Mint b) { val = b.val; return *this; }
        inline Mint operator=(int64_t b) { return *this = Mint(b); }
    	inline Mint operator+(Mint b) { return Mint(val + b.val); }
        inline Mint operator+(int64_t b) { return Mint(val + b); }
    	inline Mint operator-(Mint b) { return Mint(val - b.val); }
        inline Mint operator-(int64_t b) { return Mint(val - b); }
    	inline Mint operator*(Mint b) { return Mint(val * b.val); }
        inline Mint operator*(int64_t b) { return Mint(val * b); }
    	inline Mint operator/(Mint b) { return *this * b.invert(); }
        inline Mint operator/(int64_t b) { return *this * Mint(b).invert(); }
    	Mint invert() {
    		int64_t x, y, g = extgcd(val, MOD, x, y);
    		assert(g == 1); return Mint(x);
    	}
    	inline Mint operator^(int64_t e) {
    		if (!e) return Mint(1);
    		Mint r = *this ^ (e / 2); r = r * r;
    		return e&1 ? *this * r : r;
    	}
    };

    template <int64_t MOD> istream& operator>>(istream& in, mint<MOD>& n) { return in>>n.val; }
    template <int64_t MOD> ostream& operator<<(ostream& out, mint<MOD> n) { return out<<n.val; }
}
using namespace modInt;

const int MOD = 1e9 + 7;
const int MAX = 3e5 + 10;
mint<MOD> fac[MAX];
mint<MOD> ifac[MAX];

int64_t nCr(int n, int r){
    if (n < 0 || n < r || r < 0) return 0;
    return (fac[n] * ifac[n-r] * ifac[r]).val;
}

int64_t catalan(int n){
	return (mint<MOD>(nCr(n+n, n)) / (n+1)).val;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int64_t t, n, k, i, r, c;

    ifac[0] = fac[0] = 1;
	for(i = 1; i < MAX; i++)
        fac[i] = fac[i - 1] * i;
	ifac[MAX - 1] = fac[MAX - 1].invert();
	for(i = MAX - 2; i; i--)
        ifac[i] = ifac[i + 1] * (i + 1);

    cin>>t;
    while(t--){
        cin>>n>>k;
        for (i = 0; i < k; ++i){
            cin>>r>>c;
            n -= 1 + (r != c);
        }

        mint<MOD> ans = 0;
        for (i = n&1; i <= n; i += 2)
            ans = ans + ((fac[n-i] * ifac[(n-i)/2]) * nCr(n, n-i));
        cout<<ans<<endl;
    }

    return 0;
}
