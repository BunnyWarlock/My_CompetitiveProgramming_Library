// Author: Johan Sannemo, pajenegod, chilli
// Tested here:
// https://cses.fi/problemset/task/1135

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
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

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, q, i, u, v, val;
    cin>>n>>q;
    vector<vector<int>> g(n, vector<int>());
    for (i = 1; i < n; ++i){
        cin>>u>>v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    LCA temp(g);

    while(q--){
        cin>>u>>v;
        --u, --v;
        cout<<temp.dist(u, v)<<endl;
    }

    return 0;
}
