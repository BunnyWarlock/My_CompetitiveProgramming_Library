// Author: Sahil Yasar
// Tested here:
// https://lightoj.com/problem/pimp-my-ride

#include <iostream>
#include <cstring>
using namespace std;
#define endl '\n'

const int MAX = 15;
int a[MAX][MAX];
int dp[1<<MAX];
int n;
int solve(int mask = 0){
  if (mask == (1<<n) - 1)
    return 0;
  int& ans = dp[mask];
  if (ans != -1)
    return ans;
  ans = 1e9;
  for (int i = 0; i < n; ++i){
    if ((mask>>i)&1) continue;
    int cur = a[i][i];
    for (int j = 0; j < n; ++j)
      cur += ((mask>>j)&1) * a[i][j];
    ans = min(ans, cur + solve(mask|(1<<i)));
  }
  return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    int t, i, j, loop = 1;
    cin>>t;
    while(t--){
      cin>>n;

      for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
          cin>>a[i][j];

      memset(dp, -1, sizeof(dp[0])*(1<<n));

      cout<<"Case "<<(loop++)<<": "<<solve()<<endl;
    }

    return 0;
}
