// Author: Simon Lindholm, Sahil Yasar
// Tested here:
// https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1960

#include <iostream>
#include <sys/time.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
#define endl '\n'

typedef uint64_t ull;
static int C1, C2; // initialized below

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
// typedef A<1000000007, unsigned> H; // Use this for single hashing

void init(){
	timeval tp;
	gettimeofday(&tp, 0);
	C1 = (int)tp.tv_usec * 3731LL % 998244353;
	C2 = (int)tp.tv_usec * 2999LL % 998244353;
}

struct Hash2D{
    vector<vector<H>> hs;
    vector<H> p1, p2;
    int n, m;
    Hash2D(){}
    Hash2D(vector<string>& s){
        n = (int)s.size(), m = (int)s[0].size();
        p1.resize(m+1); p1[0] = 1;
        p2.resize(n+1); p2[0] = 1;
        for (int i = 1; i <= m; ++i) p1[i] = p1[i-1] * C1;
        for (int i = 1; i <= n; ++i) p2[i] = p2[i-1] * C2;

        hs.assign(n+1, vector<H>(m+1));
        for (int i = 0; i <= max(n, m); ++i)
            hs[min(n, i)][0] = hs[0][min(m, i)] = H();
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                hs[i][j] = hs[i][j-1]*C1 + hs[i-1][j]*C2 -
                           hs[i-1][j-1]*C1*C2 + s[i-1][j-1];
    }
    H getHash(int x1, int y1, int x2, int y2){
        // assert(x1 >= 0 && x1 <= x2 && x2 < n);
        // assert(y1 >= 0 && y1 <= y2 && y2 < m);
        int dx = x2-x1+1, dy = y2-y1+1;
        return hs[x2+1][y2+1] - hs[x2+1][y1]*p1[dy] -
               hs[x1][y2+1]*p2[dx] + hs[x1][y1]*p1[dy]*p2[dx];
    }
    H getHash(){ return getHash(0, 0, n-1, m-1); }
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

	init();
	int t, n, m, x, y, i, j, ans;
    cin>>t;
    while(t--){
        cin>>n>>m;
        vector<string> t(n);
        for (i = 0; i < n; ++i)
            cin>>t[i];
        Hash2D a(t);

        cin>>x>>y;
        vector<string> p(x);
        for (i = 0; i < x; ++i)
            cin>>p[i];
        ull b = (ull)Hash2D(p).getHash();

        ans = 0;
        for (i = 0; i <= n-x; ++i)
            for (j = 0; j <= m-y; ++j){
                ull temp = (ull)a.getHash(i, j, i+x-1, j+y-1);
                ans += (b == temp);
            }
        cout<<ans<<endl;
    }

    return 0;
}
