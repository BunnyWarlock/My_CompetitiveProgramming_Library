// Author: Sahil Yasar
// Tested on:
// https://lightoj.com/problem/how-many-zeroes

#include <iostream>
#include <string>
#include <cstring>
using namespace std;
#define endl '\n'

typedef long long ll;
ll DP[12][12][2];
ll m, n;
string num;

ll digitDP(int pos, int cnt, bool tight, bool zero){
    if (pos == num.size())
        return (zero)?1 :cnt;
    if(DP[pos][cnt][tight] != -1)
        return DP[pos][cnt][tight];
    ll res = 0, lim, digit;
    lim = (tight)?num[pos]-'0' :9;
    for (digit = 0; digit <= lim; ++digit)
        res += digitDP(pos+1, cnt+(!zero && digit==0),
              (tight && digit==lim), (zero && digit==0));
    return (zero)?res :DP[pos][cnt][tight] = res;
}

ll solve(ll x){
    if (x < 0) return 0;
    num = to_string(x);
    memset(DP, -1, sizeof(DP));
    return digitDP(0, 0, 1, 1);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    int t, loop = 1;
    cin>>t;
    while(t--){
        cin>>m>>n;
        cout<<"Case "<<(loop++)<<": ";
        cout<<solve(n)-solve(m-1)<<endl;
    }

    return 0;
}
