// Author: Simon Lindholm
// Modified by: Sahil Yasar
// Tested here:
// https://www.spoj.com/problems/NHAY/
// https://open.kattis.com/problems/hashing

#include <iostream>
#include <sys/time.h>
#include <vector>
#include <string>
using namespace std;
#define endl '\n'

typedef uint64_t ull;
static int C; // initialized below

// Arithmetic mod two primes and 2^32 simultaneously.
// "typedef uint64_t H;" instead if Thue-Morse does not apply.
template<int M, class B>
struct A {
	int x; B b; A(int x = 0): x(x), b(x) {}
	A(int x, B b): x(x), b(b) {}
	A operator+(A o){ int y = x+o.x; return{ y - (y>=M)*M, b+o.b }; }
	A operator-(A o){ int y = x-o.x; return{ y + (y< 0)*M, b-o.b }; }
	A operator*(A o) { return { (int)(1LL*x*o.x % M), b*o.b }; }
	explicit operator ull() { return x ^ (ull) b << 21; }
	bool operator==(A o) const { return (ull)*this == (ull)o; }
	bool operator<(A o) const { return (ull)*this < (ull)o; }
};
typedef A<1000000007, A<1000000009, unsigned>> H;

vector<H> pw;

struct HashInterval {
	vector<H> ha;
	HashInterval(string& str) : ha(str.size()+1){
		for (int i = 0; i < str.size(); ++i)
			ha[i+1] = ha[i] * C + str[i];
	}
	H hashInterval(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
};

// Get hash of all substring in str of a specific length
vector<H> getHashes(string& str, int length) {
	if (str.size() < length) return {};
	H h = 0;
	for (int i = 0; i < length; ++i)
		h = h * C + str[i];
	vector<H> ret = {h};
	for (int i = length; i < str.size(); ++i)
		ret.push_back(h = h * C + str[i] - pw[length] * str[i-length]);
	return ret;
}

H hashString(string& s){
	H h{};
	for(char c: s)
		h = h*C + c;
	return h;
}

void init(const int MAX = 3e5 + 10){
	timeval tp;
	gettimeofday(&tp, 0);
	C = (int)tp.tv_usec; // (less than modulo)
	// assert((ull)(H(1)*2+1-3) == 0);

    pw.resize(MAX);
    pw[0] = 1;
    for (int i = 1; i < MAX; ++i)
        pw[i] = pw[i-1] * C;
}

H concatHash(H a, H b, int len){
    return a*pw[len] + b;
}

void pointUpdateHash(H& a, string& s, char c, int i){
    a = a + pw[s.size()-1-i]*(c-s[i]);
}

vector<int> robinKarp(string text, string pattern){
	vector<int> ind;
	vector<H> hashes = getHashes(text, pattern.size());
	ull h = (ull)hashString(pattern);
	for (int i = 0; i < hashes.size(); ++i)
		if ((ull)hashes[i] == h)
			ind.push_back(i);
	return ind;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);

	init();
	int n;
	string p, t;
	while(cin>>n>>p>>t){
		vector<int> ans = robinKarp(t, p);
		for (auto& x: ans)
			cout<<x<<endl;
		cout<<endl;
	}

	/*int q, l, r;
	string s;
	cin>>s;
	HashInterval hash(s);
	cin>>q;
	while(q--){
		cin>>l>>r;
		cout<<(ull)hash.hashInterval(l, r)<<endl;
	}*/

    return 0;
}
