// Author: Sahil Yasar
// Tested here:
// https://www.spoj.com/problems/MDIGITS/

#include <iostream>
#include <string>
#include <algorithm>
#include <array>
using namespace std;
#define endl '\n'

typedef long long ll;

const int MAX = 9;
ll pow10[MAX];
array<int, 10> DP[MAX][2]; // states are (pos, zero)

void preCalc(){
    pow10[0] = 1;
    for (int i = 1; i < MAX; ++i)
        pow10[i] = pow10[i-1]*10;

    // Base case
    DP[0][0] = array<int, 10>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    DP[0][1] = array<int, 10>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    for (int pos = 1; pos < MAX; ++pos)
        for (int zero = 0; zero <= 1; ++zero){
            // Adding digit 1 or 2 or ... or 9 at pos
            for (int i = 1; i <= 9; ++i)
                DP[pos][zero][i] += 9*DP[pos-1][0][i] + pow10[pos];
            DP[pos][zero][0] += 9*DP[pos-1][0][0];
            // Adding digit 0 at pos
            for (int i = 0; i <= 9; ++i)
                DP[pos][zero][i] += DP[pos-1][zero][i];
            DP[pos][zero][0] += (!zero)*pow10[pos];
        }
}

array<int, 10> digitDP(ll x){
    if (x <= 0) return array<int, 10>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    if (x < 10){
        array<int, 10> ret{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (int i = 1; i <= x; ++i)
            ++ret[i];
        return ret;
    }

    string num = to_string(x);
    reverse(num.begin(), num.end());
    ll suffix[num.size()];
    suffix[0] = 0;
    for (int i = 0; i < num.size(); ++i)
        suffix[i+1] = pow10[i]*(num[i]-'0') + suffix[i];

    array<int, 10> ret = DP[num.size()-2][1];
    for (int i = 0; i <= num[0]-'0'; ++i)
        ++ret[i];
    for (int pos = 1; pos < num.size(); ++pos){
        int lim = num[pos]-'0';
        // Adding digit 0 or 1 or ... or lim-1 at pos
        for (int i = 0; i <= 9; ++i)
            ret[i] += (lim-(pos == num.size()-1))*DP[pos-1][0][i];
        for (int i = (pos == num.size()-1); i < lim; ++i)
            ret[i] += pow10[pos];
        // Adding digit lim at pos
        ret[lim] += suffix[pos]+1;
    }
    return ret;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    preCalc();
    int a, b, i;
    while(cin>>a>>b, a || b){
        if (a > b) swap(a, b);
        array<int, 10> ans1 = digitDP(b);
        array<int, 10> ans2 = digitDP(a-1);
        for (i = 0; i < 9; ++i)
            cout<<ans1[i]-ans2[i]<<" ";
        cout<<ans1[i]-ans2[i]<<endl;
    }

    return 0;
}
