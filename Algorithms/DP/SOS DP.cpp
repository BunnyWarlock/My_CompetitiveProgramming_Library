// Author: Sahil Yasar
// Tested here:
// https://cses.fi/problemset/task/1654
// https://codeforces.com/problemset/problem/449/D

#include <iostream>
using namespace std;
#define endl '\n'

typedef long long ll;
const int BITS = 20;
const int MAX = (1<<BITS);
ll freq[MAX];

void forward1(ll dp[]){ // adding from subset to superset
    for (int i = 0; i < BITS; ++i)
        for (int mask = 0; mask < MAX; ++mask)
            dp[mask] += ((mask>>i)&1) * dp[mask^(1<<i)];
}
void backward1(ll dp[]){
    for (int i = 0; i < BITS; ++i)
        for (int mask = MAX-1; mask >= 0; --mask)
            dp[mask] -= ((mask>>i)&1) * dp[mask^(1<<i)];
}

void forward2(ll dp[]){ // adding from superset to subset
    for (int i = 0; i < BITS; ++i)
        for (int mask = 0; mask < MAX; ++mask)
            dp[mask^(1<<i)] += ((mask>>i)&1) * dp[mask];
}
void backward2(ll dp[]){
    for (int i = 0; i < BITS; ++i)
        for (int mask = MAX-1; mask >= 0; --mask)
            dp[mask^(1<<i)] -= ((mask>>i)&1) * dp[mask];
}

const int MOD = 1e9 + 7;
ll powMod(ll x, ll p, ll m){
    ll ans = 1;
    x %= m;
    if (!x) return 0;
    while(p){
        if (p&1)
            ans = (ans*x)%m;
        p = p>>1;
        x = (x*x)%m;
    }
    return ans;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, i;
    cin>>n;
    int a[n];
    for (i = 0; i < n; ++i){
        cin>>a[i];
        ++freq[a[i]];
    }

    forward2(freq);
    for (i = 0; i < MAX; ++i)
        freq[i] = powMod(2, freq[i], MOD) - 1;
    backward2(freq);
    cout<<((freq[0] % MOD) + MOD) % MOD<<endl;

    return 0;
}
