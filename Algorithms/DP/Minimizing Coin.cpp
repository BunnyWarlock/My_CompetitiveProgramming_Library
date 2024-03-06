// Author: Sahil Yasar
// Tested here:
// https://cses.fi/problemset/task/1634/

#include <iostream>
using namespace std;
#define endl '\n'

const int INT_MAX = 1e9;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    int64_t n, x, i, j, k, ans;
    cin>>n>>x;
    int c[n];
    for (i = 0; i < n; ++i)
      cin>>c[i];

    k = x + 1;
    int dp[k];
    fill(dp, dp+k, INT_MAX);
    dp[0] = 0;
    for (j = 0; j < n; ++j)
      for (i = 1; i < k; ++i)
        if (i - c[j] >= 0)
          dp[i] = min(dp[i], dp[i-c[j]]+1);

    ans = dp[x];
    if (ans >= INT_MAX) ans = -1;
    cout<<ans<<endl;

    return 0;
}
