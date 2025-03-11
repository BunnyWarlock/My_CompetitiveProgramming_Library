// Author: Sahil Yasar
// Tested here:
// https://dmoj.ca/problem/fibonacci2
// https://judge.yosupo.jp/problem/multiplication_of_big_integers
// https://judge.yosupo.jp/problem/addition_of_big_integers

#include <iostream>
#include <complex>
#include <bitset>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
#define endl '\n'

const int MAXB = 4e5;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef complex<double> C;
typedef vector<double> vd;
const ld PI = acos(-1.0L);

void fft(vector<C>& a) {
	int n = a.size(), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, PI / k);
		for (int i = k; i < 2*k; ++i) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	vector<int> rev(n);
	for (int i = 0; i < n; ++i) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	for (int i = 0; i < n; ++i) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) for (int j = 0; j < k; ++j) {
			C z = rt[j+k] * a[i+j+k];
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}

namespace bigInt{
	using INT1 = ll; // or int
	using INT2 = __int128_t; // or ll
	const int POW = 18; // or 9
	const int POW2 = 4; // Used for mulFFT, as conv give precision errors for high bases. 6 works for ld, but slower.
	const int POW3 = 60; // Used for toBits. 31 works for base 1e9
	const ll base = 1e18; // or 1e9
	typedef vector<INT1> lnum;


	// Random
	bool isEven(const lnum& a){
		if (a.empty()) return false;
		return a[0]%2 == 0;
	}
	int sgn(const lnum& a){
		if (a.empty()) return 0;
		return (a.back() < 0)? -1: 1;
	}
	void neg(lnum& a){
		if (!a.empty()) a.back() *= -1;
	}
	void absolute(lnum& a){
		if (!a.empty()) a.back() *= sgn(a);
	}
	void trim(lnum& a){
		while (!a.empty() && !a.back())
		    a.pop_back();
	}


	// Comparison
	bool operator>(const lnum& a, const lnum& b){
		if (sgn(a) != sgn(b)) return sgn(a) > sgn(b);
		int sign = sgn(a);
		if (sign == 0) return false;
		if (a.size() != b.size())
			return a.size()*sign > b.size()*sign;
		for (int i = (int)a.size()-1; i >= 0; --i)
			if (a[i] != b[i]) return a[i]*sign > b[i]*sign;
		return false;
	}
	bool operator<(const lnum& a, const lnum& b){
		return (b > a);
	}
	bool operator>=(const lnum& a, const lnum& b){
		return !(a < b);
	}
	bool operator<=(const lnum& a, const lnum& b){
		return !(a > b);
	}
	bool operator==(const lnum& a, const lnum& b){
		if (sgn(a) != sgn(b)) return false;
		if (sgn(a) == 0) return true;
		if (a.size() != b.size()) return false;
		for (int i = 0; i < a.size(); ++i)
			if (a[i] != b[i])
				return false;
		return true;
	}
	bool operator!=(const lnum& a, const lnum& b){
		return !(a == b);
	}


	// Read and Write
	ostream& operator<<(ostream& out, const lnum& a){
	    out<<(a.empty()?0:a.back());
	    for (int i=(int)a.size()-2; i>=0; --i)
	        out<<setfill('0')<<setw(POW)<<a[i];
		return out;
	}
	lnum toBigInt(const string& s){
		lnum a; bool negated = false;
	    for (int i=(int)s.length(); i > 0; i -= POW){
	        if (i < POW){
				if (i == 1 && s[0] == '-') negated = true;
	            else a.push_back((INT1)stoll(s.substr(0, i)));
			}
	        else
	            a.push_back((INT1)stoll(s.substr(i-POW, POW)));
	    }
	    trim(a);
		if (negated) neg(a);
	    return a;
	}
	istream& operator>>(istream& in, lnum& a){
		string s;
		in>>s;
		a = toBigInt(s);
		return in;
	}


	// Addition and Subtraction
	void add(lnum& a, const lnum& b){
	    INT1 carry = 0;
	    for (size_t i = 0; i < max(a.size(), b.size()) || carry; ++i){
	        if (i == a.size()) a.push_back(0);
	        a[i] += carry + ((i < b.size())? b[i]: 0);
	        carry = (a[i] >= base);
	        if (carry)  a[i] -= base;
	    }
	}
	void sub(lnum& a, lnum& b){
		bool swapped = (b > a);
		if (swapped) swap(a, b);
		INT1 carry = 0;
		for (size_t i = 0; i < b.size() || carry; ++i){
		    a[i] -= carry + ((i < b.size())? b[i]: 0);
		    carry = (a[i] < 0);
		    if (carry)  a[i] += base;
		}
		trim(a);
		if (swapped) neg(a);
	}
	lnum operator+(lnum a, lnum& b){
		int sgn1 = sgn(a), sgn2 = sgn(b);
		absolute(a); absolute(b);
		if (sgn1 == sgn2 || sgn1 == 0 || sgn2 == 0){
			add(a, b);
			if (sgn1 == -1 || sgn2 == -1) neg(a);
		}
		else{
			sub(a, b);
			if (sgn1 == -1) neg(a);
		}
		if (sgn2) neg(b);
		return a;
	}
	lnum operator-(lnum a, lnum& b){
		neg(b);
		a = a + b;
		neg(b);
		return a;
	}


	// Multiplication
	lnum mulSimple(lnum& a, lnum& b){
		int sgn1 = sgn(a), sgn2 = sgn(b);
		absolute(a); absolute(b);
	    lnum c (a.size()+b.size());
	    for (size_t i=0; i < a.size(); ++i)
	        for (INT1 j = 0, carry = 0; j < b.size() || carry; ++j) {
	            INT2 cur = c[i+j] + (INT2)a[i] * ((j < b.size())? b[j]: 0) + carry;
	            c[i+j] = INT1(cur % base);
	            carry = INT1(cur / base);
	        }
	    trim(c);
		if (sgn1 == -1) neg(a);
		if (sgn2 == -1) neg(b);
		if (sgn1*sgn2 == -1) neg(c);
	    return c;
	}
	lnum convertBase(const lnum& a, int old_digits, int new_digits){
		vector<INT2> p(max(old_digits, new_digits) + 1);
		p[0] = 1;
		for (int i = 1; i < p.size(); i++)
			p[i] = p[i - 1] * 10;
		lnum res;
		INT2 cur = 0;
		INT1 cur_digits = 0;
		for (int i = 0; i < a.size(); i++) {
			cur += a[i] * p[cur_digits];
			cur_digits += old_digits;
			while (cur_digits >= new_digits) {
				res.push_back(INT2(cur % p[new_digits]));
				cur /= p[new_digits];
				cur_digits -= new_digits;
			}
		}
		res.push_back((INT1)cur);
		while (!res.empty() && !res.back())
			res.pop_back();
		return res;
	}
	vd conv(const lnum& a, const lnum& b) {
		if (a.empty() || b.empty()) return {};
		vd res(a.size() + b.size() - 1);
		int L = 32 - __builtin_clz(res.size()), n = 1 << L;
		vector<C> in(n), out(n);
		copy(a.begin(), a.end(), begin(in));
		for (int i = 0; i < b.size(); ++i) in[i].imag(b[i]);
		fft(in);
		for (C& x : in) x *= x;
		for (int i = 0; i < n; ++i) out[i] = in[-i & (n - 1)] - conj(in[i]);
		fft(out);
		for (int i = 0; i < res.size(); ++i) res[i] = imag(out[i]) / (4 * n);
		return res;
	}
	lnum mulFFT(lnum& a, lnum& b){
		int sgn1 = sgn(a), sgn2 = sgn(b);
		absolute(a); absolute(b);
		lnum a2 = convertBase(a, POW, POW2);
		lnum b2 = convertBase(b, POW, POW2);
		if (sgn1 == -1) neg(a);
		if (sgn2 == -1) neg(b);
		vd temp = conv(a2, b2);
		lnum c(a2.size() + b2.size());
		INT2 carry = 0, x, i;
		for (i = 0; i < temp.size(); ++i){
			x = INT2(round(temp[i])) + carry;
			carry = x / base;
			c[i] = x % base;
		}
		if (carry) c[i] = carry;
		c = convertBase(c, POW2, POW);
		if (sgn1*sgn2 == -1) neg(c);
		return c;
	}
	lnum operator*(lnum& a, lnum& b){
		if (a.size()*1LL*b.size() <= 1000000)
			return mulSimple(a, b);
		return mulFFT(a, b);
	}
	lnum operator*(lnum a, const ll b){ // b < base
	    INT1 carry = 0;
	    for (size_t i = 0; i < a.size() || carry; ++i) {
	        if (i == a.size())
	            a.push_back (0);
	        INT2 cur = carry + (INT2)a[i] * b;
	        a[i] = INT1(cur % base);
	        carry = INT1(cur / base);
	    }
	    trim(a);
	    return a;
	}


	// Division
	lnum operator/(lnum a, const ll b){ // b < base
	    INT1 carry = 0;
	    for (int i = (int)a.size()-1; i >= 0; --i) {
	        INT2 cur = a[i] + (INT2)carry * base;
	        a[i] = INT1(cur / b);
	        carry = INT1(cur % b);
	    }
	    trim(a);
	    return a;
	}


	// Modulo
	ull operator%(lnum& a, const ull m){
		__uint128_t ret = 0;
		for (int i = (int)a.size()-1; i >= 0; --i)
			ret = (ret*base + a[i]) % m;
		return (ull)ret;
	}


	// Bitset support
	bitset<MAXB> toBits(lnum a){
		bitset<MAXB> ret;
		int i = 0;
		while(!a.empty() && !(a.size() == 1 && a[0] == 0)){
			ull temp = a%((ull)1<<POW3);
			for (int j = 0; j < POW3; ++j, ++i)
				ret[i] = (temp>>j)&1;
			a = a/((ll)1<<POW3);
		}
		return ret;
	}
	lnum get(bitset<MAXB>& b){
		lnum ret = {0};
        for (int i = MAXB/POW3*POW3, j = 0; i < MAXB; ++i, ++j)
            ret[0] = ret[0]|((INT1)b[i]<<j);
		for (int i = MAXB/POW3*POW3-1; i >= 0; i -= POW3){
			lnum temp = {0};
			for (int j = 0; j < POW3 && i-j >= 0; ++j)
				temp[0] = temp[0]|((INT1)b[i-j]<<(POW3-j-1));
			ret = ret*((ll)1<<POW3) + temp;
		}
		return ret;
	}
};
using namespace bigInt;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

	int n;
	lnum a, b;
	cin>>n;
	while(n--){
		cin>>a>>b;
		a = a*b;
		cout<<a<<endl;
	}

    return 0;
}
