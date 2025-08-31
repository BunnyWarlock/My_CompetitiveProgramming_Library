// Author: Sahil Yasar
// Gonna be tested here: LightOJ is down :(
// https://lightoj.com/problem/1205

#include <iostream>
#include <string>
using namespace std;
#define endl '\n'

int64_t binExp(int64_t x, int64_t p){
    int64_t ans = 1;
    while(p){
        if (p&1)
            ans *= x;
        p = p>>1;
        x *= x;
    }
    return ans;
}

int64_t dp[20][20][20];
int vis[20][20][20], cur = 0;
string num;
int64_t digitDP(int pos, int lo, int hi){
    if (pos > (num.size()-1)/2) return (lo <= hi);
    if (vis[pos][lo][hi] == cur) return dp[pos][lo][hi];
    vis[pos][lo][hi] = cur;
    int64_t ret = 0;
    for (int digit = (pos == 0); digit <= 9; ++digit){
        int l = lo, h = hi;
        if (digit < num[pos]-'0') l = min(l, pos);
        if (digit < num[num.size()-1-pos]-'0') l = min(l, (int)num.size()-1-pos);
        if (digit > num[pos]-'0') h = min(h, pos);
        if (digit > num[num.size()-1-pos]-'0') h = min(h, (int)num.size()-1-pos);
        ret += digitDP(pos+1, l, h);
    }
    return dp[pos][lo][hi] = ret;
}

int64_t solve(int64_t n){
    if (n < 0) return 0;
    ++cur;
    num = to_string(n);
    int64_t ret = digitDP(0, num.size(), num.size());
    for (int i = 1; i < num.size(); ++i)
        ret += 9*binExp(10, (i-1)/2);
    return ret+1;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int64_t t, a, b, loop = 1;
    cin>>t;
    while(t--){
        cin>>a>>b;
        if (a > b) swap(a, b);
        cout<<"Case "<<(loop++)<<": "<<solve(b)-solve(a-1)<<endl;
    }

    return 0;
}
