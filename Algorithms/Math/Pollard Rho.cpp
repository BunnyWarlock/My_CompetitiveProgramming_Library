// Aurthor: chilli, SJTU, pajenegod, c1729, Ramchandra Apte, Noam527, Simon Lindholm
// Tested here:
// https://vjudge.net/contest/237942#problem/F

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define endl '\n'

typedef long long ll;
typedef unsigned long long ull;
// typedef __int128_t i128;
// typedef __uint128_t u128;
typedef pair<int, int> pii;

ull modmul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}

ull modpow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}

bool millerRabin(ull n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	    s = __builtin_ctzll(n-1), d = n >> s;
	for (ull a : A) {   // ^ count trailing zeroes
		ull p = modpow(a%n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}

ull gcd(ull a, ull b) {
    if (!a || !b)
        return a | b;
    unsigned shift = __builtin_ctz(a | b);
    a >>= __builtin_ctz(a);
    do {
        b >>= __builtin_ctz(b);
        if (a > b) swap(a, b);
        b -= a;
    } while (b);
    return a << shift;
}

ull pollard(ull n) {
	auto f = [n](ull x) { return modmul(x, x, n) + 1; };
	ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while (t++ % 40 || gcd(prd, n) == 1) {
		if (x == y) x = ++i, y = f(x);
		if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return gcd(prd, n);
}
vector<ull> factor(ull n) {
	if (n == 1) return {};
	if (millerRabin(n)) return {n};
	ull x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), r.begin(), r.end());
	return l;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

	ull a, i, j, cnt, ans;
	cin>>a;
	vector<ull> f = factor(a);
	sort(f.begin(), f.end());
	ans = 1;
	for (i = 0; i < f.size(); i = j){
		cnt = 1, j = i+1;
		while(j < f.size() && f[j] == f[i])
			++cnt, ++j;
		ans *= cnt+1;
	}
	cout<<ans<<endl;

    return 0;
}
