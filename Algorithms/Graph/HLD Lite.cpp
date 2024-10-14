// Author: Benjamin Qi, Oleksandr Kulkov, chilli, Sahil Yasar, Lucian Bicsi
// Description: Decomposes a tree into vertex disjoint heavy paths and light
// edges such that the path from any leaf to the root contains at most log(n)
// light edges. Code does additive modifications and max queries, but can
// support commutative segtree modifications/queries on paths and subtrees.
// Takes as input the full adjacency list. VALS\_EDGES being true means that
// values are stored in the edges, as opposed to the nodes. All values
// initialized to the segtree default. Root must be 0.
// Time: O((log N)^2)
// Tested here:
// https://cses.fi/problemset/task/2134/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define endl '\n'

#define INT_MIN -1e9-10

struct Tree {
	typedef int T;
	static constexpr T unit = INT_MIN;
	T f(T a, T b) { return max(a, b); } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

template <bool VALS_EDGES> struct HLD {
	int N, tim = 0;
	vector<vector<int>> adj;
	vector<int> par, siz, rt, pos;
	Tree *tree;
	HLD(vector<vector<int>> adj_)
		: N(adj_.size()), adj(adj_), par(N, -1), siz(N, 1),
		  rt(N),pos(N),tree(new Tree(N)){ dfsSz(0); dfsHld(0); }
	void dfsSz(int v) {
		if (par[v] != -1) adj[v].erase(find(adj[v].begin(), adj[v].end(), par[v]));
		for (int& u : adj[v]) {
			par[u] = v;
			dfsSz(u);
			siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfsHld(int v) {
		pos[v] = tim++;
		for (int u : adj[v]) {
			rt[u] = (u == adj[v][0] ? rt[v] : u);
			dfsHld(u);
		}
	}
	template <class B> void process(int u, int v, B op) {
		for (; rt[u] != rt[v]; v = par[rt[v]]) {
			if (pos[rt[u]] > pos[rt[v]]) swap(u, v);
			op(pos[rt[v]], pos[v] + 1);
		}
		if (pos[u] > pos[v]) swap(u, v);
		op(pos[u] + VALS_EDGES, pos[v] + 1);
	}
    void update(int u, int val){
        process(u, u, [&](int l, int r) { tree->update(l, val); });
    }
	int queryPath(int u, int v) { // Modify depending on problem
		int res = -1e9;
		process(u, v, [&](int l, int r) {
				res = max(res, tree->query(l, r));
		});
		return res;
	}
    int querySubtree(int v) { // modifySubtree is similar
		return tree->query(pos[v] + VALS_EDGES, pos[v] + siz[v]);
	}
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, q, i, u, v, op, ans;
    cin>>n>>q;
    int val[n];
    for (i = 0; i < n; ++i)
        cin>>val[i];
    vector<vector<int>> adj(n, vector<int>());
    for (i = 1; i < n; ++i){
        cin>>u>>v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    HLD<false> hld(adj);
    for (i = 0; i < n; ++i)
        hld.update(i, val[i]);

    while(q--){
        cin>>op>>u>>v;
        if (op == 1){
            --u;
            hld.update(u, v);
        }
        else{
            --u, --v;
            ans = hld.queryPath(u, v);
            cout<<ans<<" ";
        }
    }
    cout<<endl;

    return 0;
}
