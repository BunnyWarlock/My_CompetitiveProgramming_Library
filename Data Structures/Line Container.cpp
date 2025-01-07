// Author: Simon Lindholm
// Description: Container where you can add lines of the form mx+c, and query maximum values at points x.
// Useful for dynamic programming (convex hull trick).
// Time: O(log N)
// Tested here:
// https://atcoder.jp/contests/dp/tasks/dp_z

#include <iostream>
#include <set>
#include <climits>
#include <cassert>
using namespace std;
#define endl '\n'

typedef long long ll;

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll m, ll c) {
		auto z = insert({m, c, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll n, c, i;
    cin>>n>>c;
    ll h[n], dp[n];
    for (i = 0; i < n; ++i)
        cin>>h[i];

    LineContainer l;
    // l.clear();
    dp[0] = 0;
    l.add(2*h[0], -(h[0]*h[0] + dp[0]));
    for (i = 1; i < n; ++i){
        dp[i] = c + h[i]*h[i] - l.query(h[i]);
        l.add(2*h[i], -(h[i]*h[i] + dp[i]));
    }
    cout<<dp[n-1]<<endl;

    return 0;
}
