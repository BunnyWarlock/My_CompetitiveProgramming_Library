#include <iostream>
#include <unordered_map>
#include <math.h>
#include <algorithm>
using namespace std;
#define endl '\n'

int64_t discrete_log(int64_t a, int64_t b, int64_t m){
    a %= m, b %= m;
    int64_t k = 1, add = 0, g, i, n, e, cur;

    for (g = __gcd(a, m); g > 1; g = __gcd(a, m)){
        if (b == k)
            return add;
        if (b % g)
            return -1;
        b /= g, m /= g, ++add;
        k = (k * a / g) % m;
    }

    n = ceil(sqrt(1.0 * m));
    e = 1;
    unordered_map<int64_t, int64_t> vals;
    for (i = 0; i < n; ++i){
        vals[(e * b) % m] = i;
        e = (e * a) % m;
    }

    for (i = 1, cur = k; i <= n; ++i) {
        cur = (cur * e) % m;
        if (vals.count(cur))
            return n * i - vals[cur] + add;
    }
    return -1;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int64_t t, a, b, m;
    cin>>t;
    while(t--){
      cin>>a>>b>>m;
      cout<<discrete_log(a, b, m)<<endl;
    }

    return 0;
}
