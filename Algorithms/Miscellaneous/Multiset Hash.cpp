// Author: Sahil Yasar
// Tested here:
// https://atcoder.jp/contests/abc367/tasks/abc367_f

#include <iostream>
#include <sys/time.h>
#include <vector>
using namespace std;
#define endl '\n'

typedef uint64_t ull;
typedef pair<ull, ull> P;
static int K; // initialized below
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;

void init(){
	timeval tp;
	gettimeofday(&tp, 0);
	K = (int)tp.tv_usec * 3731LL % 998244353;
}

ull powMod(ull x, ull p, ull m){
    ull ans = 1;
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

ull updateHash(ull hash, int num, ull mod, bool add = 1){
    ull temp = num + K;
    if (!add) temp = powMod(temp, mod-2, mod);
    return hash * temp % mod;
}
P updateHash(P hash, int num, bool add = 1){
    return {updateHash(hash.first, num, MOD1, add),
            updateHash(hash.second, num, MOD2, add)};
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    init();
    int n, q, i, l1, r1, l2, r2;
    cin>>n>>q;
    int a[n], b[n];
    P p1[n+1], p2[n+1];
    p1[0] = p2[0] = {1, 1};
    for (i = 0; i < n; ++i){
        cin>>a[i];
        p1[i+1] = updateHash(p1[i], a[i]);
    }
    for (i = 0; i < n; ++i){
        cin>>b[i];
        p2[i+1] = updateHash(p2[i], b[i]);
    }

    auto rangeHash = [&](P h[], int l, int r) -> P{
        return {h[r+1].first * powMod(h[l].first, MOD1-2, MOD1) % MOD1,
                h[r+1].second * powMod(h[l].second, MOD2-2, MOD2) % MOD2};
    };

    while(q--){
        cin>>l1>>r1>>l2>>r2;
        --l1, --r1, --l2, --r2;
        if (rangeHash(p1, l1, r1) == rangeHash(p2, l2, r2))
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
    }

    return 0;
}
