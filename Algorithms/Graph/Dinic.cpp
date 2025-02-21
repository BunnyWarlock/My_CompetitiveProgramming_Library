// Author: chilli
// Source: https://cp-algorithms.com/graph/dinic.html
// Description: Flow algorithm with complexity O(VE*log U) where U = max |capacity|.
// O(min(E^{1/2}, V^{2/3})E) if U = 1; O(sqrt{V}E) for bipartite matching.
// Tested here:
// https://codeforces.com/gym/103743/problem/B

#include <iostream>
#include <vector>
#include <climits>
#include <bitset>
using namespace std;
#define endl '\n'

typedef long long ll;

struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vector<int> lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0) {
		adj[a].push_back({b, (int)adj[b].size(), c, c});
		adj[b].push_back({a, (int)adj[a].size() - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < adj[v].size(); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		for (int L = 0; L < 31; ++L) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vector<int>(q.size());
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};


const ll MAX = 2e4 + 10;
bitset<MAX> primes;
void sieve(){
    primes.set();
    primes[0] = primes[1] = false;
    for (int i = 4; i < MAX; i+=2)
        primes[i] = false;
    for (int i = 3; i*i <= MAX; i+=2){
        if (!primes[i]) continue;
        for (int j=i*i; j < MAX; j+=i+i)
            primes[j] = false;
    }
}

vector<int> g[MAX/2];
bitset<MAX/2> vis;
vector<vector<int>> ans;
void dfs(int s){
    vis[s] = true;
    ans.back().push_back(s);
    for (auto u: g[s])
        if (!vis[u])
            dfs(u);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    sieve();
    ll n, i, j, temp;
    cin>>n;

    Dinic f(n+2);
    for (i = 1; i <= n; i += 2){
        f.addEdge(0, i, 2);
        f.addEdge(i+1, n+1, 2);
    }
    for (i = 1; i <= n; i += 2)
        for (j = 2; j <= n; j += 2)
            if (primes[i+j])
                f.addEdge(i, j, 1);

    temp = f.calc(0, n+1);
    if (temp != n){
        cout<<"-1"<<endl;
        return 0;
    }
    for (i = 1; i <= n; i += 2)
        for (auto& x: f.adj[i])
            if (x.flow() == 1){
                g[i].push_back(x.to);
                g[x.to].push_back(i);
            }
    for (i = 1; i <= n; ++i)
        if (!vis[i]){
            ans.emplace_back();
            dfs(i);
        }

    cout<<ans.size()<<endl;
    for (auto& v: ans){
        cout<<v.size()<<" ";
        for (i = 0; i+1 < v.size(); ++i)
            cout<<v[i]<<" ";
        cout<<v.back()<<endl;
    }

    return 0;
}
