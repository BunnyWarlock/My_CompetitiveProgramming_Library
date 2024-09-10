// Author: Sahil Yasar
// Tested here:
// https://codeforces.com/contest/321/problem/C

#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
#define endl '\n'

const int MAX = 1e5 + 10;
vector<int> g[MAX];
char ans[MAX];
int sz[MAX];
bitset<MAX> dead;

void dfs(int v, int p = -1){
    sz[v] = 1;
    for (int u: g[v])
        if (u != p && !dead[u]){
            dfs(u, v);
            sz[v] += sz[u];
        }
}

int findCentroid(int num, int v, int p = -1){
    for (int u: g[v])
        if (u != p && !dead[u] && 2*sz[u] > num)
            return findCentroid(num, u, v);
    return v;
}

void decompose(int v, char c){
    dfs(v);
    int cent = findCentroid(sz[v], v);
    ans[cent] = c;
    dead[cent] = true;
    for (int u: g[cent])
        if (!dead[u])
            decompose(u, c+1);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, i, u, v;;
    cin>>n;
    for (i = 1; i < n; ++i){
        cin>>u>>v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dead.reset();
    decompose(0, 'A');

    for (i = 0; i < n; ++i)
        cout<<ans[i]<<" ";
    cout<<endl;

    return 0;
}
