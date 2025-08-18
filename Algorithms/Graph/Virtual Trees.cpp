// Author: Simon Lindholm, Sahil Yasar
// Description: Given a rooted tree and a subset S of nodes, compute the minimal
// subtree that contains all the nodes by adding all (at most |S|-1)
// pairwise LCA's and compressing edges.
// Stores the adjacency matrix of the virtual tree in vt
// Returns the root and size of the virtual tree
// Modified from kactl CompressTree.h
// Time: O(|S|log|S|)
// Tested here:
// https://atcoder.jp/contests/abc359/tasks/abc359_g

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <bitset>
using namespace std;
#define endl '\n'

// Time: O(|V|log |V| + Q)
template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= V.size(); pw *= 2, ++k) {
			jmp.emplace_back(V.size() - pw * 2 + 1);
			for (int j = 0; j < jmp[k].size(); ++j)
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
    // rmq.query(inclusive, exclusive);
	T query(int a, int b) {
		// assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct LCA {
	int T = 0;
	vector<int> time, path, ret, depth;
	RMQ<int> rmq;

	LCA(vector<vector<int>>& C): time(C.size()), depth(C.size()),
                                 rmq((dfs(C,0,-1), ret)) {}
	void dfs(vector<vector<int>>& C, int v, int par, int d = 0){
		time[v] = T++;
        depth[v] = d;
		for (int y : C[v]) if (y != par){
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v, d+1);
		}
	}

	int lca(int a, int b){
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	int dist(int a,int b){
        return depth[a] + depth[b] - 2*depth[lca(a,b)];
    }
};

const int MAX = 2e5 + 10;
vector<pair<int, int>> vt[MAX];
bitset<MAX> S; // Stores whether the node is in the subset or not
pair<int, int> virtualTree(LCA& lca, const vector<int>& subset){
	vector<int> nod = subset, &T = lca.time;
	auto cmp = [&](int a, int b) { return T[a] < T[b]; };
	sort(nod.begin(), nod.end(), cmp);
	int m = nod.size();
	for (int i = 1; i < m; ++i){
		int a = nod[i-1], b = nod[i];
		nod.push_back(lca.lca(a, b));
	}
	sort(nod.begin(), nod.end(), cmp);
	nod.erase(unique(nod.begin(), nod.end()), nod.end());
	for (int i = 0; i < nod.size(); ++i){
        vt[nod[i]].clear();
        S[nod[i]] = false;
    }
	for (int i = 1; i < nod.size(); ++i) {
		int u = lca.lca(nod[i-1], nod[i]), v = nod[i], w = lca.dist(u, v);
		vt[u].emplace_back(v, w); vt[v].emplace_back(u, w);
	}
    for (auto x: subset) S[x] = true;
	return {nod[0], nod.size()};
}

int64_t ans, sz;
int dfs(int u, int p = -1){
    int ret = S[u], temp;
    for (auto [v, w]: vt[u])
        if (v != p){
            ret += temp = dfs(v, u);
            ans += w * 1LL * temp * 1LL * (sz-temp);
        }
    return ret;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int64_t n, i, u, v;
    cin>>n;
    vector<vector<int>> g(n);
    for (i = 1; i < n; ++i){
        cin>>u>>v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    LCA lca(g);

    pair<int, int> a[n];
    for (i = 0; i < n; ++i){
        cin>>a[i].first;
        a[i].second = i;
    }
    sort(a, a+n);
    vector<vector<int>> s;
    for (i = 0; i < n; ){
        s.emplace_back();
        s.back().push_back(a[i].second);
        for (++i; i < n && a[i].first == a[i-1].first; ++i)
            s.back().push_back(a[i].second);
    }

    ans = 0;
    for (auto v: s){
        sz = v.size();
        dfs(virtualTree(lca, v).first);
    }
    cout<<ans<<endl;

    return 0;
}
