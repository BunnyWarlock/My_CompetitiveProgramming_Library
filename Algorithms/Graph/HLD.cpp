// Author: Benjamin Qi, Oleksandr Kulkov, chilli, Lucian Bicsi
// Description: Decomposes a tree into vertex disjoint heavy paths and light
// edges such that the path from any leaf to the root contains at most log(n)
// light edges. Code does additive modifications and max queries, but can
// support commutative segtree modifications/queries on paths and subtrees.
// Takes as input the full adjacency list. VALS\_EDGES being true means that
// values are stored in the edges, as opposed to the nodes. All values
// initialized to the segtree default. Root must be 0.
// Time: O((log N)^2)
// Tested here:
// https://codeforces.com/gym/102040/submission/286088758
// https://www.spoj.com/problems/QTREE/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
#define endl '\n'

const int INF = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, mset = INF, madd = 0, val = -INF;
	Node(int lo,int hi):lo(lo),hi(hi){}
	Node(vector<int>& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = max(l->val, r->val);
		}
		else val = v[lo];
	}
    void getVal(vector<int>& v, int lo, int hi){
        if (lo + 1 < hi) {
            push();
			int mid = lo + (hi - lo)/2;
			l->getVal(v, lo, mid); r->getVal(v, mid, hi);
		}
		else v[lo] = val;
    }
	int query(int L, int R) {
		if (R <= lo || hi <= L) return -INF;
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != INF) mset += x;
			else madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != INF)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = INF;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

template <bool VALS_EDGES> struct HLD {
	int N, tim = 0;
	vector<vector<int>> adj;
	vector<int> par, siz, rt, pos;
	Node *tree;
	HLD(vector<vector<int>> adj_)
		: N(adj_.size()), adj(adj_), par(N, -1), siz(N, 1),
		  rt(N),pos(N),tree(new Node(0, N)){ dfsSz(0); dfsHld(0); }
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
	void modifyPath(int u, int v, int val) {
		process(u, v, [&](int l, int r) { tree->add(l, r, val); });
	}
    void modify(int u, int val) {
		process(u, u, [&](int l, int r) { tree->add(l, r, val); });
	}
    void updatePath(int u, int v, int val){
        process(u, v, [&](int l, int r) { tree->set(l, r, val); });
    }
    void update(int u, int val){
        process(u, u, [&](int l, int r) { tree->set(l, r, val); });
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
    vector<int> getVal(){
        vector<int> temp(N), v(N);
        tree->getVal(temp, pos[0] + VALS_EDGES, pos[0] + siz[0]);
        for (int i = 0; i < N; ++i)
            v[i] = temp[pos[i]];
        return v;
    }
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t, n, i, j, ans;
    string s;
    cin>>t;
    while(t--){
        cin>>n;
        int u[n-1], v[n-1], w[n-1];
        vector<vector<int>> adj(n, vector<int>());
        for (i = 0; i < n-1; ++i){
            cin>>u[i]>>v[i]>>w[i];
            --u[i], --v[i];
            adj[u[i]].push_back(v[i]);
            adj[v[i]].push_back(u[i]);
        }
        HLD<true> hld(adj);
        for (i = 0; i < n-1; ++i)
            hld.updatePath(u[i], v[i], w[i]);

        while(true){
            cin>>s;
            if (s == "DONE")
                break;
            cin>>i>>j;
            if (s == "CHANGE"){
                --i;
                hld.updatePath(u[i], v[i], j);
            }
            else{
                --i, --j;
                ans = hld.queryPath(i, j);
                cout<<ans<<endl;
            }
        }
    }


    return 0;
}
