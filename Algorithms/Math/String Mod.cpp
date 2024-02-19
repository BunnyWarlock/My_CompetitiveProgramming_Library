// Author: Sahil Yasar
// Tested manually. Answer checked through wolfram alpha

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

typedef long long ll;
// Ideally blk should be pow(10, floor(log10(1e18/mod)))
ll strMod(string s, ll mod, int blk = 9) {
    ll x = 0, i, temp = pow(10, blk), n = s.size();
    for (i = 0; i < n; i += blk)
        x = (x*((i+blk<=n)?temp:(ll)pow(10, n-i)) +
            stoll(s.substr(i, blk))) % mod;
    return x;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    string s;
    int n;
    cin>>s>>n;
    cout<<strMod(s, n)<<endl;

    return 0;
}
