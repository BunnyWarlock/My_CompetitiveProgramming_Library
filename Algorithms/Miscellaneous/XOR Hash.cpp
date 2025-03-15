// Author: Sahil Yasar
// Tested here:
// https://atcoder.jp/contests/abc295/tasks/abc295_d

#include <iostream>
#include <string>
#include <map>
using namespace std;
#define endl '\n'

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    srand(time(0));
    int64_t i, ans, cur;
    int64_t r[10];
    for (i = 0; i < 10; ++i)
        r[i] = rand();
    string s;
    cin>>s;
    map<int64_t, int> cnt;
    ++cnt[0];
    cur = ans = 0;
    for (i = 0; i < s.length(); ++i){
        cur ^= r[s[i]-'0'];
        ans += cnt[cur];
        ++cnt[cur];
    }
    cout<<ans<<endl;

    return 0;
}
