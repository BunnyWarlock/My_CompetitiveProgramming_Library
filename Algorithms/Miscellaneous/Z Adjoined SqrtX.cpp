// Author: Sahil Yasar
// Z adjoined sqrt(X) or Z[sqrt(X)] struct
// Tested here:
// https://dmoj.ca/problem/fibonacci2

#include <iostream>
#include <cassert>
#include <bitset>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
#define endl '\n'

const int MAXB = 4e5;
typedef long long ll;
typedef unsigned long long ull;

namespace rootNumberSystem{
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
		inline rx operator^(ll e) {
			if (!e) return rx(1);
			rx z = *this ^ (e / 2); z = z * z;
			return e&1 ? *this * z : z;
		}
		inline rx operator^(bitset<MAXB>& b){
			rx ans(1); rx z = *this;
			for (int i = 0; i < MAXB; ++i){
				if (b[i]) ans = ans * z;
				z = z * z;
			}
			return ans;
		}
		inline rx conj() { return rx(a, b*-1); }
	};

	template <class T, int X> ostream& operator<<(ostream& out, rootX<T, X> z) {
		return out<<z.a<<" + "<<z.b<<"sqrt("<<X<<") ";
	}
}
using namespace rootNumberSystem;

namespace modInt{
    ll extgcd(ll a, ll b, ll& x, ll& y) {
        if (!b){ x = 1, y = 0; return a; }
        ll res = extgcd(b, a%b, y, x);
        y -= (a/b)*x;
        return res;
    }

    template <const ll MOD>
    struct mint{
        ll val;
        using Mint = mint<MOD>;
        mint(): val(0) {}
        mint(ll x) { val = ((x % MOD) + MOD) % MOD; }
        inline Mint operator=(Mint b) { val = b.val; return *this; }
        inline Mint operator=(ll b) { return *this = Mint(b); }
    	inline Mint operator+(Mint b) { return Mint(val + b.val); }
        inline Mint operator+(ll b) { return Mint(val + b); }
    	inline Mint operator-(Mint b) { return Mint(val - b.val); }
        inline Mint operator-(ll b) { return Mint(val - b); }
    	inline Mint operator*(Mint b) { return Mint(val * b.val); }
        inline Mint operator*(ll b) { return Mint(val * b); }
    	inline Mint operator/(Mint b) { return *this * b.invert(); }
        inline Mint operator/(ll b) { return *this * Mint(b).invert(); }
    	Mint invert() {
    		ll x, y, g = extgcd(val, MOD, x, y);
    		assert(g == 1); return Mint(x);
    	}
    	inline Mint operator^(ll e) {
    		if (!e) return Mint(1);
    		Mint r = *this ^ (e / 2); r = r * r;
    		return e&1 ? *this * r : r;
    	}
    };

    template <ll MOD> istream& operator>>(istream& in, mint<MOD>& n) { return in>>n.val; }
    template <ll MOD> ostream& operator<<(ostream& out, mint<MOD> n) { return out<<n.val; }
}
using namespace modInt;

namespace bigInt{
	using INT1 = ll; // or int
	using INT2 = __int128_t; // or ll
	const int POW = 18; // or 9
	const ll base = 1e18; // or 1e9
	typedef vector<INT1> lnum;

	void print(lnum& a){
	    cout<<(a.empty()?0:a.back());
	    for (int i=(int)a.size()-2; i>=0; --i)
	        cout<<setfill('0')<<setw(POW)<<a[i];
	    cout<<endl;
	}

	lnum get(string& s){
	    lnum a;
	    for (int i=(int)s.length(); i > 0; i -= POW){
	        if (i < POW)
	            a.push_back((INT1)stoll(s.substr (0, i)));
	        else
	            a.push_back((INT1)stoll(s.substr (i-POW, POW)));
	    }
	    while (a.size() > 1 && a.back() == 0)
	        a.pop_back();
	    return a;
	}

	lnum operator+(lnum a, const lnum& b){
	    INT1 carry = 0;
	    for (size_t i=0; i < max(a.size(),b.size()) || carry; ++i) {
	        if (i == a.size())
	            a.push_back (0);
	        a[i] += carry + (i < b.size() ? b[i] : 0);
	        carry = a[i] >= base;
	        if (carry)  a[i] -= base;
	    }
	    return a;
	}

	lnum operator-(lnum a, const lnum& b){
		INT1 carry = 0;
		for (size_t i=0; i < b.size() || carry; ++i) {
		    a[i] -= carry + (i < b.size() ? b[i] : 0);
		    carry = a[i] < 0;
		    if (carry)  a[i] += base;
		}
		while (a.size() > 1 && a.back() == 0)
		    a.pop_back();
		return a;
	}

	lnum operator*(lnum a, const lnum& b){
	    lnum c (a.size()+b.size());
	    for (size_t i=0; i < a.size(); ++i)
	        for (INT1 j = 0, carry = 0; j < b.size() || carry; ++j) {
	            INT2 cur = c[i+j] + (INT2)a[i] * ((j < b.size())? b[j]: 0) + carry;
	            c[i+j] = INT1(cur % base);
	            carry = INT1(cur / base);
	        }
	    while (c.size() > 1 && c.back() == 0)
	        c.pop_back();
	    return c;
	}

	lnum operator*(lnum a, const ll b){
	    INT1 carry = 0;
	    for (size_t i = 0; i < a.size() || carry; ++i) {
	        if (i == a.size())
	            a.push_back (0);
	        INT2 cur = carry + (INT2)a[i] * b;
	        a[i] = INT1(cur % base);
	        carry = INT1(cur / base);
	    }
	    while (a.size() > 1 && a.back() == 0)
	        a.pop_back();
	    return a;
	}

	lnum operator/(lnum a, const ll b){
	    INT1 carry = 0;
	    for (int i = (int)a.size()-1; i >= 0; --i) {
	        INT2 cur = a[i] + (INT2)carry * base;
	        a[i] = INT1(cur / b);
	        carry = INT1(cur % b);
	    }
	    while (a.size() > 1 && a.back() == 0)
	        a.pop_back();
	    return a;
	}

	ull operator%(lnum& a, const ull m){
		__uint128_t ret = 0;
		for (int i = (int)a.size()-1; i >= 0; --i)
			ret = (ret*base + a[i]) % m;
		return (ull)ret;
	}

	bool isEven(lnum& a){
		if (a.empty()) return false;
		return a[0]%2 == 0;
	}

	bitset<MAXB> toBits(lnum a){
		bitset<MAXB> ret;
		int i = 0;
		while(!a.empty() && !(a.size() == 1 && a[0] == 0)){
			// ull temp = a%((ull)0x80000000);
			ull temp = a%((ull)0x1000000000000000);
			// for (int j = 0; j < 31; ++j, ++i)
			for (int j = 0; j < 60; ++j, ++i)
				ret[i] = (temp>>j)&1;
			// a = a/((ll)0x80000000);
			a = a/((ll)0x1000000000000000);
		}
		return ret;
	}
};
using namespace bigInt;

const int MOD = 1e9 + 7;
typedef rootX<mint<MOD>, 5> r5;
mint<MOD> half = mint<MOD>(2).invert();
mint<MOD> fifth = mint<MOD>(5).invert();

ll fib(ll n){
	r5 f = (r5(half, half)^n) - (r5(half, half*-1)^n);
	f = f*r5(0, fifth);
	return f.a.val;
}
ll fib(bitset<MAXB> n){
	r5 f = (r5(half, half)^n) - (r5(half, half*-1)^n);
	f = f*r5(0, fifth);
	return f.a.val;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

	string s;
	cin>>s;
	bitset<MAXB> b = toBits(get(s));
	cout<<fib(b)<<endl;

    return 0;
}
