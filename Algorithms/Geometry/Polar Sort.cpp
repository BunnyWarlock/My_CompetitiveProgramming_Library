// Author: Sahil Yasar
// Tested here:
// https://judge.yosupo.jp/problem/sort_points_by_argument

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#define endl '\n'

#define f first
#define s second

typedef int64_t ll;
typedef pair<ll, ll> pll;

inline int quad(ll x, ll y){
    if (x == 0 & y == 0) return 0;
    if (x > 0 && y >= 0) return 1;
    if (x <= 0 && y > 0) return 2;
    if (x < 0 && y <= 0) return 3;
    return 4;
}

inline bool cmp(pll a, pll b){
    int q1 = quad(a.f, a.s), q2 = quad(b.f, b.s);
    if (q1 != q2) return (q1 < q2);
    if (a.s*b.f == b.s*a.f)
        return (a.f*a.f + a.s*a.s <  b.f*b.f + b.s*b.s);
    return (a.s*b.f < b.s*a.f);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll n, i, j;
    cin>>n;
    pll p[n];
    for (i = 0; i < n; ++i)
        cin>>p[i].f>>p[i].s;
    sort(p, p+n, cmp);

    for (j = 0; j < n; ++j)
        if (quad(p[j].f, p[j].s) >= 3 && p[j].s != 0)
            break;
    for (i = 0; i < n; ++i)
        cout<<p[(i+j)%n].f<<" "<<p[(i+j)%n].s<<endl;

    return 0;
}
