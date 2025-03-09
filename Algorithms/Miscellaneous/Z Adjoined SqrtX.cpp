// Author: Sahil Yasar
// Z adjoined sqrt(X) or Z[sqrt(X)] struct
// Tested here:
// https://cses.fi/problemset/task/1722

#include <iostream>
#include <cassert>
using namespace std;
#define endl '\n'

namespace Z_sqrtX{
	template <class T, int X>
	struct rootX{
		T a, b; // a + b*sqrt(X)
		using rx = rootX<T, X>;
		rootX(T a = T(), T b = T()): a(a), b(b) {}
		inline rx operator=(rx z) { a = z.a, b = z.b; return *this; }
		inline rx operator=(T z) { return *this = rx(a); }
		inline rx operator+(rx z) { return rx(a+z.a, b+z.b); }
	    inline rx operator+(T z) { return rx(a+z, b); }
		inline rx operator-(rx z) { return rx(a-z.a, b-z.b); }
	    inline rx operator-(T z) { return rx(a-z, b); }
		inline rx operator*(rx z) { return rx(a*z.a + b*z.b*X, a*z.b + b*z.a); }
	    inline rx operator*(T z) { return rx(a*z, b*z); }
		inline rx operator/(rx z) {
			return (*this * z.conj()) / (z.a*z.a - z.b*z.b*X);
		}
	    inline rx operator/(T z) { return rx(a/z, b/z); }
		inline rx operator^(int64_t e) {
			if (!e) return rx(1);
			rx z = *this ^ (e / 2); z = z * z;
			return e&1 ? *this * z : z;
		}
		inline rx conj() { return rx(a, b*-1); }
	};

	template <class T, int X> ostream& operator<<(ostream& out, rootX<T, X> z) {
		return out<<z.a<<" + "<<z.b<<"sqrt("<<X<<") ";
	}
}
using namespace Z_sqrtX;

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
typedef rootX<mint<MOD>, 5> r5;
mint<MOD> half = mint<MOD>(2).invert();
mint<MOD> fifth = mint<MOD>(5).invert();

int64_t fib(int64_t n){
	r5 f = (r5(half, half)^n) - (r5(half, half*-1)^n);
	f = f*r5(0, fifth);
	return f.a.val;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

	int64_t n;
    cin>>n;
    cout<<fib(n)<<endl;

    return 0;
}
