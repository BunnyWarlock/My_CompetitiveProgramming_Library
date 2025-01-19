// Author: Jubayer Nirjhor, Sahil Yasar
// Tested here:
// https://cses.fi/problemset/task/1700

#include <iostream>
#include <vector>
using namespace std;
#define endl '\n'

void init(){ srand(time(0)); }

struct treeHash{
    vector<int> r;
    int MOD;
    treeHash(int MOD): MOD(MOD) {}
    int rng(int n){
        while((int)r.size() <= n)
            r.push_back(rand() * 1LL * rand() % MOD);
        return r[n];
    }
    int hash(vector<vector<int>>& g, int u, int& h, int p = -1){
        vector<int> child;
        for (int v: g[u])
            if (v != p){
                int temp = 0;
                child.push_back(hash(g, v, temp, u));
                h = max(h, temp+1);
            }
        if (child.empty()) return 1;
        int64_t ret = 1;
        for (int x: child)
            ret = ret * (rng(h) + x) % MOD;
        return (int)ret;
    }
    int hash(vector<vector<int>>& g, int u){
        int h = 0;
        return hash(g, u, h);
    }
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    init();
    int t, n, i, u, v;
    treeHash h1(1e9 + 7);
    treeHash h2(1e9 + 9);
    cin>>t;
    while(t--){
        cin>>n;
        vector<vector<int>> g1(n);
        vector<vector<int>> g2(n);
        for (i = 1; i < n; ++i){
            cin>>u>>v;
            --u, --v;
            g1[u].push_back(v);
            g1[v].push_back(u);
        }
        for (i = 1; i < n; ++i){
            cin>>u>>v;
            --u, --v;
            g2[u].push_back(v);
            g2[v].push_back(u);
        }

        if (h1.hash(g1, 0) == h1.hash(g2, 0) &&
            h2.hash(g1, 0) == h2.hash(g2, 0))
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }

    return 0;
}
