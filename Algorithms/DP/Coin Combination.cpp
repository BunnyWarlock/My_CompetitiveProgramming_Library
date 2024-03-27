// Author: Sahil Yasar
// Tested here:
// https://cses.fi/problemset/task/1635
// https://cses.fi/problemset/task/1636

#include <iostream>
#include <cstring>
using namespace std;
#define endl '\n'

const int MOD = 1e9 + 7;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    int n, x, i, j;
    cin>>n>>x;
    int c[n];
    for (i = 0; i < n; ++i)
      cin>>c[i];

    int64_t dp[x+1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    // Order of coins does not matter
    // for (i = 0; i <= x; ++i)
    //   for (j = 0; j < n; ++j)
    //     (dp[i] += (i >= c[j]) * dp[i-c[j]]) %= MOD;

    // Order of coins does matter
    for (i = 0; i < n; ++i)
      for (j = c[i]; j <= x; ++j)
        (dp[j] += dp[j-c[i]]) %= MOD;

    cout<<dp[x]<<endl;

    return 0;
}
