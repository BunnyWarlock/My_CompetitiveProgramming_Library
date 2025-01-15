// Author: Sahil Yasar
// Tested here:
// https://codeforces.com/problemset/problem/622/F

// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cassert>
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
    		assert(g == 1); return Mint((x + MOD) % MOD);
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

template <int MOD>
struct kth{
    int K;
    vector<mint<MOD>> y;
    kth(int k): K(k + 2){
        y.push_back(0);
        for (int i = 1; i < K; ++i)
            y.push_back(y[i-1] + (mint<MOD>(i)^k));
    }
    int64_t query(int x){
        if (x < K) return y[x].val;
        mint<MOD> ans, n = 1, d = 1;
        for (int i = 1; i < K; ++i)
            n = n * (x-i), d = d * -i;
        d = d.invert();
        ans = n * d * y[0];
        for (int i = 1; i < K; ++i){
            n = n * (x-i+1)/(x-i);
            d = d * (-K+i)/i;
            ans = ans + (n*d*y[i]);
        }
        return ans.val;
    }
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, k;
    cin>>n>>k;
    kth<1000000007> ans(k);
    cout<<ans.query(n)<<endl;

    return 0;
}
