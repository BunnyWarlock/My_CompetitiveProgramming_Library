// Author: Sahil Yasar
// Tested here:
// https://www.spoj.com/problems/ETF/
// https://lightoj.com/problem/mathematically-hard

#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
#define endl '\n'

typedef unsigned long long ull;

const int MAX = 5e6 + 10;
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

int phi(int n){
    int e = n, i;
    for (i = 0; p[i]*p[i] <= n; ++i)
        if (n%p[i] == 0){
            while(n%p[i] == 0)
                n /= p[i];
            e -= e/p[i];
        }
    if (n > 1)
        e -= e/n;
    return e;
}

vector<ull> phi_1_to_n(int n){
    vector<ull> phi(n+1);
    for (int i = 0; i <= n; ++i)
        phi[i] = i;
    for (int i = 2; i <= n; ++i)
        if (phi[i] == i)
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j]/i;
    return phi;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    // sieve();
    // int t, n;
    // cin>>t;
    // while(t--){
    //     cin>>n;
    //     cout<<phi(n)<<endl;
    // }

    int t, a, b, i, loop = 1;
    vector<ull> ans = phi_1_to_n(MAX);
    for (i = 1; i <= MAX; ++i)
        ans[i] = ans[i]*ans[i] + ans[i-1];
    cin>>t;
    while(t--){
        cin>>a>>b;
        cout<<"Case "<<(loop++)<<": "<<ans[b]-ans[a-1]<<endl;
    }

    return 0;
}
