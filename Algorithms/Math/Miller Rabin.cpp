// Author: chilli, c1729, Ramchandra Apte, Noam527, Simon Lindholm
// Tested here:
// https://www.spoj.com/problems/PON/
// Description: Deterministic Miller-Rabin primality test
// Guaranteed to work for numbers up to 7e18

#include <iostream>
using namespace std;
#define endl '\n'

typedef long long ll;
typedef unsigned long long ull;

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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

	ull t, n;
	cin>>t;
	while(t--){
		cin>>n;
		cout<<((millerRabin(n))?"YES":"NO")<<endl;
	}

    return 0;
}
