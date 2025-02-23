// Author: Chen Xing, Johan Sannemo, Simon Lindholm
// Description: Finds a minimum vertex cover in a bipartite graph.
// The size is the same as the size of a maximum matching, and
// the complement is a maximum independent set.
// Returns a vector with the vertex in the cover
// If the vertex is from the right partition then it adds n to
// the vertex number, where n is the size of the left partition.
// Tested here:
// https://www.spoj.com/problems/PT07X/

#include <iostream>
#include <vector>
#include <cassert>
#include <cstring>
using namespace std;
#define endl '\n'

typedef vector<int> vi;

bool dfs(int a, int L, vector<vi>& g, vi& btoa, vi& A, vi& B) {
	if (A[a] != L) return 0;
	A[a] = -1;
	for (int b : g[a]) if (B[b] == L + 1) {
		B[b] = 0;
		if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
			return btoa[b] = a, 1;
	}
	return 0;
}

int hopcroftKarp(vector<vi>& g, vi& btoa) {
	int res = 0;
	vi A(g.size()), B(btoa.size()), cur, next;
	while(true) {
		fill(A.begin(), A.end(), 0);
		fill(B.begin(), B.end(), 0);
		/// Find the starting nodes for BFS (i.e. layer 0).
		cur.clear();
		for (int a : btoa) if(a != -1) A[a] = -1;
		for (int a = 0; a < g.size(); ++a) if(A[a] == 0) cur.push_back(a);
		/// Find all layers using bfs.
		for (int lay = 1;; lay++) {
			bool islast = 0;
			next.clear();
			for (int a : cur) for (int b : g[a]) {
				if (btoa[b] == -1) {
					B[b] = lay;
					islast = 1;
				}
				else if (btoa[b] != a && !B[b]) {
					B[b] = lay;
					next.push_back(btoa[b]);
				}
			}
			if (islast) break;
			if (next.empty()) return res;
			for (int a : next) A[a] = lay;
			cur.swap(next);
		}
		/// Use DFS to scan for augmenting paths.
		for (int a = 0; a < g.size(); ++a)
			res += dfs(a, 0, g, btoa, A, B);
	}
}

vi cover(vector<vi>& g, int n, int m) {
	vi match(m, -1);
	int res = hopcroftKarp(g, match);
	vector<bool> lfound(n, true), seen(m);
	for (int it : match) if (it != -1) lfound[it] = false;
	vi q, cover;
	for (int i = 0; i < n; ++i) if (lfound[i]) q.push_back(i);
	while (!q.empty()) {
		int i = q.back(); q.pop_back();
		lfound[i] = 1;
		for (int e : g[i]) if (!seen[e] && match[e] != -1) {
			seen[e] = true;
			q.push_back(match[e]);
		}
	}
	for (int i = 0; i < n; ++i) if (!lfound[i]) cover.push_back(i);
	for (int i = 0; i < m; ++i) if (seen[i]) cover.push_back(n+i);
	assert(cover.size() == res);
	return cover;
}


const int MAX = 1e5 + 10;
vi tree[MAX];
vector<vi> g(MAX);
int idx[MAX];
int cnt[2] = {0, 0};
void treeToBipartite(int s, int p = -1, bool color = true){
    if (idx[s] == -1)
        idx[s] = cnt[color]++;
    for (auto u: tree[s])
        if (u != p){
            treeToBipartite(u, s, !color);
            if (color) g[idx[s]].push_back(idx[u]);
            else g[idx[u]].push_back(idx[s]);
        }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    memset(idx, -1, sizeof(idx));
    int n, u, v, i;
    cin>>n;
    for (i = 1; i < n; ++i){
        cin>>u>>v;
        --u, --v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    treeToBipartite(0);
    g.resize(cnt[1]);
    vi ans = cover(g, cnt[1], cnt[0]);
    cout<<ans.size()<<endl;

    return 0;
}
