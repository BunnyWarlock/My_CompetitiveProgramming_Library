// Author: Sahil Yasar
// Tested here:
// https://open.kattis.com/problems/stringmatching

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
vector<vector<int>> kmp(string &s, vector<int> &lps){
    vector<vector<int>> ret(1, vector<int>(128, 0));
    ++ret[0][s[0]];
    for (int i = 1; i < s.size(); ++i){
        ret.push_back(ret[lps[i-1]]);
        ret.back()[s[i]] = i+1;
    }
    return ret;
}

vector<int> match2(string &txt, string &pat){
    vector<int> ret, lps = pi(pat);
    vector<vector<int>> k = kmp(pat, lps);
    for (int i = 0, j = 0; i < txt.size(); ++i){
        j = k[j][txt[i]];
        if (j == pat.size()){
            ret.push_back(i-j+1);
            j = lps[j-1];
        }
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string a, b;
    while(getline(cin, a) && getline(cin, b)){
      vector<int> ans = match2(b, a);
      for (auto& x: ans)
        cout<<x<<" ";
      cout<<endl;
    }

    return 0;
}
