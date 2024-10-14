// Author: Sahil Yasar
// Tested here:
// https://codeforces.com/problemset/problem/1092/F

#include <iostream>
#include <vector>
using namespace std;
#define endl '\n'

typedef long long ll;
const int MAX = 2e5 + 10;
int val[MAX];
vector<int> g[MAX];
ll cs[MAX], st[MAX], dp[MAX];
void dfs(int s, int p = -1){
    cs[s] = val[s];
    st[s] = 0;
    for (int& c: g[s])
        if (c != p){
            dfs(c, s);
            cs[s] += cs[c];
            st[s] += st[c] + cs[c];
        }
}

void dfs2(int s, int p = -1){
    dp[s] = st[s];
    for (int& c: g[s])
        if (c != p){
            cs[s] -= cs[c];
            st[s] -= st[c] + cs[c];
            cs[c] += cs[s];
            st[c] += st[s] + cs[s];
            dfs2(c, s);
            st[c] -= st[s] + cs[s];
            cs[c] -= cs[s];
            st[s] += st[c] + cs[c];
            cs[s] += cs[c];
        }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll n, u, v, i, ans;
    cin>>n;
    for (i = 0; i < n; ++i)
        cin>>val[i];
    for (i = 1; i < n; ++i){
        cin>>u>>v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(0);
    dfs2(0);
    ans = dp[0];
    for (i = 0; i < n; ++i)
        ans = max(ans, dp[i]);
    cout<<ans<<endl;

    return 0;
}
