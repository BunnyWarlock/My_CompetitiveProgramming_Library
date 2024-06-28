// Author: Simon Lindholm
// Source: marian's (TC) code
// Description: Aho-Corasick automaton, used for multiple pattern matching.
// Initialize with AhoCorasick ac(patterns); the automaton start node will be at index 0.
// Duplicate patterns are allowed; empty patterns are not.
// For large alphabets, split each symbol into chunks, with sentinel bits for symbol boundaries.
// Time: construction takes O(26N), where N = sum of length of patterns.
// Tested here:
// https://lightoj.com/problem/substring-frequency-ii

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
using namespace std;
#define endl '\n'

template<char first = 'a', int alpha = 26>
struct AhoCorasick {
	struct Node {
		// (nmatches is optional)
		int back, next[alpha], start = -1, end = -1; // nmatches = 0;
        // next contains the next node along with the failure links of each node
        // end contains the index of the pattern which ends at that node or -1 otherwise
		Node(int v) { memset(next, v, sizeof(next)); }
	};
	vector<Node> N;
	vector<int> backp; 
    // backp contains the dictionary links of each pattern

	void insert(string& s, int j) {
		// assert(!s.empty());
		int n = 0;
		for (char c : s) {
			int& m = N[n].next[c - first];
			if (m == -1) { n = m = N.size(); N.emplace_back(-1); }
			else n = m;
		}
		if (N[n].end == -1) N[n].start = j;
		backp.push_back(N[n].end);
		N[n].end = j;
		// N[n].nmatches++;
	}
	AhoCorasick(vector<string>& pat): N(1, -1) {
		for(int i = 0; i < pat.size(); ++i) insert(pat[i], i);
		N[0].back = N.size();
		N.emplace_back(0);

		queue<int> q;
		for (q.push(0); !q.empty(); q.pop()) {
			int n = q.front(), prev = N[n].back;
			for (int i = 0; i < alpha; ++i) {
				int &ed = N[n].next[i], y = N[prev].next[i];
				if (ed == -1) ed = y;
				else {
					N[ed].back = y;
					(N[ed].end == -1 ? N[ed].end : backp[N[ed].start])
						= N[y].end;
					// N[ed].nmatches += N[y].nmatches;
					q.push(ed);
				}
			}
		}
	}

    // find(word) returns for each position the index of the longest word that ends there, or -1 if none.
    // find(x) is O(N), where N = length of x.
	vector<int> find(string& word) {
		int n = 0;
		vector<int> res; // ll count = 0;
        // count is total no. of matches
		for (char c : word) {
			n = N[n].next[c - first];
			res.push_back(N[n].end);
			// count += N[n].nmatches;
		}
		return res;
	}

    // findAll(-, word) finds all words (up to N*sqrt(N) many if no duplicate patterns)
    // that start at each position (shortest first).
    // findAll is O(NM).
	vector<vector<int>>findAll(vector<string>& pat, string& word) {
		vector<int> r = find(word);
		vector<vector<int>> res(word.size());
		// vector<int> res(pat.size(), 0); 
        // ^ This version counts the freq of each pattern
		for (int i = 0; i < word.size(); ++i) {
			int ind = r[i];
			while (ind != -1) {
                res[i - pat[ind].size() + 1].push_back(ind);
				// ++res[ind];
				ind = backp[ind];
			}
		}
		return res;
	}
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t, i, n, loop = 1;
    string s;
    cin>>t;
    while(t--){
        cin>>n>>s;
        vector<string> w(n);
        for (i = 0; i < n; ++i)
            cin>>w[i];
        AhoCorasick a(w);

        vector<int> ans = a.findAll(w, s);
        cout<<"Case "<<(loop++)<<":"<<endl;
        for (i = 0; i < n; ++i)
            cout<<ans[i]<<endl;
    }

    return 0;
}
