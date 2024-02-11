// Author: Sahil Yasar
// Tested here:
// https://atcoder.jp/contests/abc340/submissions/50211564

#include <iostream>
using namespace std;
#define endl '\n'

int64_t extgcd(int64_t a, int64_t b, int64_t& x, int64_t& y) {
    if (!b){ x = 1, y = 0; return a; }
    int64_t res = extgcd(b, a%b, y, x);
    y -= (a/b)*x;
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    int64_t a, b, x, y, g;
    cin>>x>>y;
    g = extgcd(x, -y, b, a);
    if (g > 2 || g < -2)
      cout<<-1<<endl;
    else{
      a = a*(2/g), b = b*(2/g);
      cout<<a<<" "<<b<<endl;
    }

    return 0;
}
