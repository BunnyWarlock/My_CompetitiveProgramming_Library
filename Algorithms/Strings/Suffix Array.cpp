// Author: Sahil Yasar
// Tested here:
// https://www.spoj.com/problems/LCS/en/

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
using namespace std;
#define endl '\n'

void suffixArray(string& s, vector<int>& sa, vector<int>& lcp, int lim=256){
	int n = s.size() + 1, k = 0, a, b, i, j, p;
	vector<int> x(s.begin(), s.end()+1), y(n), ws(max(n, lim)), rank(n);
	sa = lcp = y, iota(sa.begin(), sa.end(), 0);
	for (j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
		p = j, iota(y.begin(), y.end(), n-j);
		for(i = 0; i < n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
		fill(ws.begin(), ws.end(), 0);
		for(i = 0; i < n; ++i) ws[x[i]]++;
		for(i = 1; i < lim; ++i) ws[i] += ws[i - 1];
		for (i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
		swap(x, y), p = 1, x[sa[0]] = 0;
		for(i = 1; i < n; ++i) a = sa[i - 1], b = sa[i], x[b] =
			(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
	}
	for(i = 1; i < n; ++i) rank[sa[i]] = i;
	for (i = 0; i < n-1; lcp[rank[i++]] = k)
		for (k && k--, j = sa[rank[i] - 1];
				s[i + k] == s[j + k]; k++);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    string a, b, c;
    vector<int> sa, lcp;
    int i, ans;
    cin>>a>>b;
    c = a + "$" + b;
    suffixArray(c, sa, lcp);
    ans = 0;
    for (i = 1; i < sa.size()-1; ++i)
      if ((sa[i]<a.length() && sa[i+1]>a.length()) || (sa[i+1]<a.length() && sa[i]>a.length()))
        ans = max(ans, lcp[i+1]);
    cout<<ans<<endl;

    return 0;
}
