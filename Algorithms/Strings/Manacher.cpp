// Author: adamant, Sahil Yasar
// Source: http://codeforces.com/blog/entry/12143
// Description: For each position in a string, computes p[0][i] = half length of
// longest even palindrome around pos i, p[1][i] = longest odd (half rounded down).
// Time: O(N)
// Tested here:
// https://www.spoj.com/problems/LPS/cstart=20
// https://www.spoj.com/problems/PLSQUARE/

#include <iostream>
#include <string>
#include <array>
#include <vector>
using namespace std;
#define endl '\n'

struct Manacher{
    array<vector<int>, 2> p;
    Manacher(const string& s) {
    	int n = s.size();
    	p = {vector<int>(n+1), vector<int>(n)};
    	for (int z = 0; z < 2; ++z)
            for (int i=0,l=0,r=0; i < n; i++) {
        		int t = r-i+!z;
        		if (i<r) p[z][i] = min(t, p[z][l+t]);
        		int L = i-p[z][i], R = i+p[z][i]-!z;
        		while (L>=1 && R+1<n && s[L-1] == s[R+1])
        			p[z][i]++, L--, R++;
        		if (R>r) l=L, r=R;
        	}
    }
    bool isPalindrome(int l, int r){ // [l, r]
        int len = r-l+1;
        return (p[len&1][(l+r+1)/2]*2 + 1 >= len);
    }
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    /*int n, lps = 0, i;
    string s;
    cin>>n>>s;
    array<vector<int>, 2> arr = manacher(s);
    for (i = 0; i < n; ++i)
        lps = max(lps, max(arr[0][i]*2, arr[1][i]*2 + 1));
    cout<<lps<<endl;*/

    int n, ans, i, j, first, last, mid;
    cin>>n;
    string s[n];
    vector<Manacher> r;
    vector<Manacher> c;
    for (i = 0; i < n; ++i){
        cin>>s[i];
        Manacher a(s[i]);
        r.emplace_back(a);
    }
    for (j = 0; j < n; ++j){
        string temp = "";
        for (i = 0; i < n; ++i)
            temp += s[i][j];
        Manacher a(temp);
        c.emplace_back(a);
    }

    auto check = [&](int x){
        for (int i = 0; i <= n-x; ++i)
            for (int j = 0; j <= n-x; ++j){
                bool temp = true;
                for (int k = i; k < i+x; ++k)
                    temp &= r[k].isPalindrome(j, j+x-1);
                for (int k = j; k < j+x; ++k)
                    temp &= c[k].isPalindrome(i, i+x-1);
                if (temp)
                    return true;
            }
        return false;
    };

    ans = 0;
    for (int p: {0, 1}){
        first = 1, last = n;
        first += (first%2 != p);
        last -= (last%2 != p);
        while(first <= last){
            mid = (first+last)/2;
            mid += (mid%2 != p);
            if (check(mid)){
                ans = max(ans, mid);
                first = mid+2;
            }
            else
                last = mid-2;
        }
    }
    cout<<ans<<endl;

    return 0;
}
