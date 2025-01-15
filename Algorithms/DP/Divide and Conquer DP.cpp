// Author: Sahil Yasar
// Tested here:
// https://cses.fi/problemset/task/2086

#include <iostream>
using namespace std;
#define endl '\n'

typedef long long ll;
const ll INF = 1e17;
const int MAX = 3010;
ll p[MAX], dp[2][MAX];

ll cost(int l, int r){
    ll sum = p[r] - p[l-1];
    return sum * sum;
}

void dnc(bool prev, int l, int r, int optl, int optr){
    if (l > r) return;
    int mid = (l + r) >> 1;
    pair<ll, int> ans = {INF, optl};
    for (int i = optl; i <= min(mid, optr); ++i)
        ans = min(ans, {dp[prev][i-1] + cost(i, mid), i});
    dp[!prev][mid] = ans.first;
    int opt = ans.second;
    dnc(prev, l, mid-1, optl, opt);
    dnc(prev, mid+1, r, opt, optr);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int k, n, i;
    cin>>n>>k;
    for (i = 1; i <= n; ++i){
        cin>>p[i];
        p[i] += p[i-1];
    }

    for (i = 1; i <= n; ++i)
        dp[0][i] = INF;
    for (i = 0; i < k; ++i)
        dnc(i&1, 1, n, 1, n);
    cout<<dp[k&1][n]<<endl;
    
    return 0;
}
