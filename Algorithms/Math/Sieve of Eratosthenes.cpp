// Author: Sahil Yasar
// Tested here:
// https://www.spoj.com/problems/PRINT/

#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
#define endl '\n'

typedef long long ll;

const int LIM = 5e4;
const int MAX = 1e6 + 10;
bitset<LIM> primes;
bitset<MAX> rangePrime;
vector<int> p;

void sieve(){
  primes.set();
  primes[0] = primes[1] = false;
  for (int i = 4; i < LIM; i+=2)
    primes[i] = false;
  for (int i = 3; i*i <= LIM; i+=2){
    if (!primes[i]) continue;
    for (int j=i*i; j < LIM; j+=i+i)
      primes[j] = false;
  }
  for (int i = 0; i < LIM; ++i)
    if (primes[i])
      p.push_back(i);
}

void sieveRange(ll l, ll r){
  rangePrime.set();
  for (int i: p)
    for (ll j = max(i*1LL*i, (l+i-1)/ i*1LL*i); j <= r; j += i)
      rangePrime[j-l]= false;
  if (l == 1) rangePrime[0] = false;

  // Problem Specific. Can Ignore.
  for (int i = 0; i < r-l+1; ++i)
    if (rangePrime[i]) cout<<i+l<<endl;
  cout<<endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin.exceptions(cin.failbit);

  sieve();
  ll t, l, r;
  cin>>t;
  while(t--){
    cin>>l>>r;
    sieveRange(l, r);
  }

  return 0;
}
