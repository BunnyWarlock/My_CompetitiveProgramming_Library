// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <bitset>
#include <numeric>
using namespace std;
#define endl '\n'

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template<class T>
// using oset = tree<T, null_type, less<T>, rb_tree_tag,
//              tree_order_statistics_node_update>;

template <class ...Args> auto &print(const Args &...args)
{ return ((cerr<<args<<", "), ...)<<"\b\b)"<<endl; }
#define watch(...) if(true){cerr<<"("#__VA_ARGS__") = ("; print(__VA_ARGS__);}
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define read(arr) for(auto& x: arr) cin>>x
#define write(arr) for(auto& x: arr) cout<<x<<" "; cout<<endl
// #define mem(x, n) memset(x, n, sizeof(x))

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

const ll MAX = 1e5;
const ll MOD = 1e9+7;
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

vector<pii> pf(int x){
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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    

    return 0;
}
