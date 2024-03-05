// Author: Sahil Yasar
// Tested here:
// https://lightoj.com/problem/how-many-zeroes

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
#define endl '\n'

typedef long long ll;
ll DP[12][12][2][2];
ll m, n;
string num;

ll digitDP(int pos, int cnt, bool tight, bool zero){
    if (pos < 0)
        return (zero)?1 :cnt;
    ll& res = DP[pos][cnt][tight][zero];
    if(!tight && res != -1)
        return res;
    res = 0;
    int lim, digit;
    lim = (tight)?num[pos]-'0' :9;
    for (digit = 0; digit <= lim; ++digit)
        res += digitDP(pos-1, cnt+(!zero && digit==0),
              (tight && digit==lim), (zero && digit==0));
    return res;
}

ll solve(ll x){
    if (x < 0) return 0;
    num = to_string(x);
    reverse(num.begin(), num.end());
    return digitDP(num.size()-1, 0, 1, 1);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    memset(DP, -1, sizeof(DP));
    int t, loop = 1;
    cin>>t;
    while(t--){
        cin>>m>>n;
        cout<<"Case "<<(loop++)<<": ";
        cout<<solve(n)-solve(m-1)<<endl;
    }

    return 0;
}
