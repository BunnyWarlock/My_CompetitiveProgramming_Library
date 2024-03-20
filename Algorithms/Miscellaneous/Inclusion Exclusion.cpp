// Author: Sahil Yasar
// Tested here:
// https://toph.co/p/towers-of-doom

#include <iostream>
#include <algorithm>
using namespace std;
#define endl '\n'

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    int t, n, s, i, j, mask, lcm, temp, ans, loop = 1;
    cin>>t;
    while(t--){
      cin>>n>>s;
      int h[n], arr[s], pile[n];
      for (i = 0; i < n; ++i){
        cin>>h[i];
        pile[i] = 0;
      }
      for (i = 0; i < s; ++i)
        cin>>arr[i];

      for (mask = 1; mask < (1<<s); ++mask){
        lcm = 1;
        for (i = 0; i < s; ++i)
          if ((mask>>i)&1)
            lcm = lcm / __gcd(lcm, arr[i]) * arr[i];

        temp = (__builtin_popcount(mask)&1)?1:-1;

        for (i = 0; i < n; ++i)
          pile[i] += temp * (h[i]/lcm + 1);
      }

      ans = 0;
      for (i = 0; i < n; ++i)
        ans ^= pile[i];
      cout<<"Case "<<(loop++)<<": "<<((ans)?"Alice":"Bob")<<endl;
    }

    return 0;
}
