// Author: Sahil Yasar
// Tested here:
// https://codeforces.com/contest/321/problem/C
// https://codeforces.com/problemset/problem/342/E

#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <tuple>
using namespace std;
#define endl '\n'

const int MAX = 1e5 + 10;
const int INF = 1e9 + 10;
vector<vector<int>> g;
int sz[MAX], pc[MAX], ans[MAX];
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

void decompose(int v, int p = -1){
    dfs(v);
    int cent = findCentroid(sz[v], v);
    pc[cent] = p;
    dead[cent] = true;
    for (int u: g[cent])
        if (!dead[u])
            decompose(u, cent);
}

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

void updateNode(int n, LCA &temp){
    ans[n] = 0;
    int p = pc[n];
    while(p != -1){
        ans[p] = min(ans[p], temp.dist(n, p));
        p = pc[p];
    }
}

int solve(int n, LCA &temp){
    int x = ans[n], p = pc[n];
    while(p != -1){
        x = min(x, temp.dist(n, p) + ans[p]);
        p = pc[p];
    }
    return x;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m, i, u, v, val;
    cin>>n>>m;
    g.assign(n, vector<int>());
    for (i = 1; i < n; ++i){
        cin>>u>>v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    LCA temp(g);
    dead.reset();
    decompose(0);
    fill(ans, ans+n, INF);
    updateNode(0, temp);

    while(m--){
        cin>>u>>v;
        --v;
        if (u == 1)
            updateNode(v, temp);
        else
            cout<<solve(v, temp)<<endl;
    }

    return 0;
}
