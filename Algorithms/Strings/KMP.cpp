// Author: Sahil Yasar
// Tested here:
// https://open.kattis.com/problems/stringmatching
// https://vjudge.net/problem/UVA-10712

#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define endl '\n'

vector<int> pi(string &s) {
	vector<int> p(s.size());
	for(int i = 1, g; i < s.size(); ++i) {
		g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}

vector<int> match(string &txt, string &pat){
    vector<int> m, lps = pi(pat);
    int i = 0, j = 0;
    while(i < txt.size()){
        if (pat[j] == txt[i])
            ++j, ++i;
        if (j == pat.size()){
            m.push_back(i-j);
            j = lps[j-1];
        }
        if (i < txt.size() && pat[j] != txt[i]){
            if (j) j = lps[j-1];
            else ++i;
        }
    }
    return m;
}

// Useful for some string DP
vector<vector<int>> kmp(string &s){
    vector<int> lps = pi(s);
    vector<vector<int>> ret(s.size(), vector<int>(10, 0));
    for (int i = 0; i < s.size(); ++i)
        for (int j = '0'; j <= '9'; ++j){
            int k = i;
            while(k > 0){
                if (s[k] == j) break;
                k = lps[k-1];
            }
            ret[i][j-'0'] = k+(s[k] == j);
        }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string a, b;
    while(getline(cin, a) && getline(cin, b)){
      vector<int> ans = match(b, a);
      for (auto& x: ans)
        cout<<x<<" ";
      cout<<endl;
    }

    return 0;
}
