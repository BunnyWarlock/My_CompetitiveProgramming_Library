// Author: Sahil Yasar
// Tested here:
// https://codeforces.com/gym/104822/problem/I
// O(sqrt(n) / ln(n))

#include <iostream>
#include <vector>
#include <bitset>
#include <map>
using namespace std;
#define endl '\n'

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const ll MAX = 1e5;
bitset<MAX> primes;
vector<int> p;

void sieve(){
  primes.set();
  primes[0] = primes[1] = false;
  for (int i = 4; i < MAX; i+=2)
    primes[i] = false;
  for (int i = 3; i*i <= MAX; i+=2){
    if (!primes[i]) continue;
    for (int j=i*i; j < MAX; j+=i+i)
      primes[j] = false;
  }
  for (int i = 0; i < MAX; ++i)
    if (primes[i])
      p.push_back(i);
}

vector<pii> primeFactorization(int x){
  vector<pii> v;
  for (int i = 0; p[i]*p[i] <= x; ++i){
    if (x%p[i]) continue;
    int temp = 0;
    while(x%p[i] == 0){
      ++temp;
      x /= p[i];
    }
    v.push_back({p[i], temp});
  }
  if (x != 1)
    v.push_back({x, 1});
  return v;
}

void solve(vector<pii>& pf, ull& ans, ull a, ull curDiv = 1, int i = 0){
    if (i == pf.size() || curDiv > a){
		if (curDiv > a)
	        ans = min(ans, curDiv);
        return;
    }
    ull j, k = 1;
    for (j = 0; j <= pf[i].second; ++j){
        solve(pf, ans, a, curDiv*k, i+1);
        k *= pf[i].first;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    sieve();
    ull t, a, i, ans;
    map<ll, ll> memo;
    cin>>t;
    while(t--){
        cin>>a;
        if (memo.count(a)){
            cout<<memo[a]<<endl;
            continue;
        }

        vector<pii> pf = primeFactorization(a);
        for (i = 0; i < pf.size(); ++i)
            pf[i].second += pf[i].second;

        ans = a*a;
		    solve(pf, ans, a);
        memo[a] = ans-a;
        cout<<ans-a<<endl;
    }

    return 0;
}
