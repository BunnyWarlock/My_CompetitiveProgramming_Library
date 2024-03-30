// Author: Sahil Yasar
// Tested here:
// https://codeforces.com/contest/1407/problem/B

#include <iostream>
#include <algorithm>
using namespace std;
#define endl '\n'

int gcd(int a, int b) {
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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    int t, n, i, j, mx, g;
    cin>>t;
    while(t--){
        cin>>n;
        int a[n];
        for (i = 0; i < n; ++i)
            cin>>a[i];
        sort(a, a+n, greater<>());
        g = a[0];
        cout<<a[0]<<" ";
        for (i = 1; i < n; ++i){
            mx = i;
            for (j = i+1; j < n; ++j)
                if (gcd(g, a[j]) > gcd(g, a[mx]))
                    mx = j;
            cout<<a[mx]<<" ";
            g = gcd(g, a[mx]);
            swap(a[i], a[mx]);
        }
        cout<<endl;
    }

    return 0;
}
