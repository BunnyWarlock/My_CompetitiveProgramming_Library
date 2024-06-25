// Author: Sahil Yasar, Simon Lindholm
// Tested here:
// https://atcoder.jp/contests/abc331/tasks/abc331_f

#include <iostream>
#include <sys/time.h>
#include <vector>
#include <string>
#include <algorithm>
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

void init(int MAX = 1e6 + 10){
	timeval tp;
	gettimeofday(&tp, 0);
	C = (int)tp.tv_usec; // (less than modulo)
	// assert((ull)(H(1)*2+1-3) == 0);

    pw.resize(MAX);
    pw[0] = 1;
    for (int i = 1; i < MAX; ++i)
        pw[i] = pw[i-1] * C;
}

namespace segmentTreeHash{
    struct HSEGtree{
        vector<H> arr;
        string S;

        void build(int v, int tl, int tr){
            if (tl == tr){
                arr[v] = S[tl];
                return;
            }
            int tm = (tl + tr) / 2;
            build(v+1, tl, tm);
            build(v+2*(tm-tl+1), tm+1, tr);
            arr[v] = arr[v+1]*pw[tr-tm] + arr[v+2*(tm-tl+1)];
        }
        HSEGtree(string& s){
            S = s;
            arr.resize(2*S.size()-1);
            build(0, 0, S.size()-1);
        }

        H query(int v, int tl, int tr, int l, int r){
            if (l > tr || r < tl)
                return H{};
            if (l <= tl && r >= tr)
                return arr[v] * pw[r-tr];
            int tm = (tl + tr) / 2;
            return query(v+1, tl, tm, l, r) +
                   query(v+2*(tm-tl+1), tm+1, tr, l, r);
        }
        H query(int l, int r){
            return query(0, 0, S.size()-1, l, r);
        }

        void update(int v, int tl, int tr, int pos, char c){
            if (tl == tr){
                arr[v] = S[pos] = c;
                return;
            }
            int tm = (tl + tr) / 2;
            if (pos <= tm) update(v+1, tl, tm, pos, c);
            else update(v+2*(tm-tl+1), tm+1, tr, pos, c);
            arr[v] = arr[v+1]*pw[tr-tm] + arr[v+2*(tm-tl+1)];
        }
        void update(int pos, char c){
            update(0, 0, S.size()-1, pos, c);
        }
    };
}
using namespace segmentTreeHash;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

	init();
    int n, q, i, l, r;
    char c;
    string s;
    cin>>n>>q>>s;
    HSEGtree a(s);
    reverse(s.begin(), s.end());
    HSEGtree b(s);

    while(q--){
        cin>>i;
        if (i == 1){
            cin>>l>>c;
            a.update(--l, c);
            b.update(n-1-l, c);
        }
        else{
            cin>>l>>r;
            --l, --r;
            bool ans = ((ull)a.query(l, r) == (ull)b.query(n-1-r, n-1-l));
            cout<<((ans)?"Yes":"No")<<endl;
        }
    }

    return 0;
}
