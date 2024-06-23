// Author: adamant
// Source: http://codeforces.com/blog/entry/12143
// Description: For each position in a string, computes p[0][i] = half length of
// longest even palindrome around pos i, p[1][i] = longest odd (half rounded down).
// Time: O(N)
// Tested here:
// https://www.spoj.com/problems/LPS/cstart=20

#include <iostream>
#include <string>
#include <array>
#include <vector>
using namespace std;
#define endl '\n'

array<vector<int>, 2> manacher(const string& s) {
	int n = s.size();
	array<vector<int>,2> p = {vector<int>(n+1), vector<int>(n)};
	for (int z = 0; z < 2; ++z)
        for (int i=0,l=0,r=0; i < n; i++) {
    		int t = r-i+!z;
    		if (i<r) p[z][i] = min(t, p[z][l+t]);
    		int L = i-p[z][i], R = i+p[z][i]-!z;
    		while (L>=1 && R+1<n && s[L-1] == s[R+1])
    			p[z][i]++, L--, R++;
    		if (R>r) l=L, r=R;
    	}
	return p;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, lps = 0, i;
    string s;
    cin>>n>>s;
    array<vector<int>, 2> arr = manacher(s);
    for (i = 0; i < n; ++i)
        lps = max(lps, max(arr[0][i]*2, arr[1][i]*2 + 1));
    cout<<lps<<endl;

    return 0;
}
