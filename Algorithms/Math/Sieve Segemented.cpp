// Author: Jakob Kogler, chilli, pajenegod
// Produces all primes below LIM
// LIM = 1e9, Time = 1.5s approx
// https://ideone.com/XO6Vwx

#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>
#include <array>
using namespace std;
#define endl '\n'

const int LIM = 1e9;
bitset<LIM> isPrime;
vector<int> segmentedSieve() {
	const int S = (int)round(sqrt(LIM)), R = LIM / 2;
	vector<int> pr = {2}, sieve(S+1); pr.reserve(int(LIM/log(LIM)*1.1));
	vector<pair<int, int>> cp;
	for (int i = 3; i <= S; i += 2) if (!sieve[i]) {
		cp.push_back({i, i * i / 2});
		for (int j = i * i; j <= S; j += 2 * i) sieve[j] = 1;
	}
	for (int L = 1; L <= R; L += S) {
		array<bool, S> block{};
		for (auto &[p, idx] : cp)
			for (int i=idx; i < S+L; idx = (i+=p)) block[i-L] = 1;
		for(int i = 0; i < min(S, R - L); ++i)
			if (!block[i]) pr.push_back((L + i) * 2 + 1);
	}
	for (int i : pr) isPrime[i] = 1;
	return pr;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

		vector<int> p = segmentedSieve();
		cout<<p.size()<<endl;

    return 0;
}
