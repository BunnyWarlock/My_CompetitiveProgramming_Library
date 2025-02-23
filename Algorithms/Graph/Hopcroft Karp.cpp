// Author: Chen Xing
// Description: Fast bipartite matching algorithm. Graph g should be a list
// of neighbors of the left partition, and btoa should be a vector full of
// -1's of the same size as the right partition. Returns the size of
// the matching. btoa[i] will be the match for vertex $i$ on the right side,
// or -1 if it's not matched.
// Usage: vi btoa(m, -1); hopcroftKarp(g, btoa);
// Time: O(sqrt{V}E)
// Tested here:
// https://www.spoj.com/problems/MATCHING/

#include <iostream>
#include <vector>
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

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m, p, i, a, b;
    cin>>n>>m>>p;
    vector<vi> g(n);
    for (i = 0; i < p; ++i){
        cin>>a>>b;
        --a, --b;
        g[a].push_back(b);
    }
    vi btoa(m, -1);
    cout<<hopcroftKarp(g, btoa)<<endl;

    return 0;
}
