// Author: Sahil Yasar
// Tested here:
// https://lightoj.com/problem/an-easy-lcs

#include <iostream>
#include <string>
using namespace std;
#define endl '\n'

string cmp(string a, string b){
    if (a > b) swap(a, b);
    if (a.size() < b.size()) swap(a, b);
    return a;
}

string lcs(string a, string b){
    string dp[a.size()+1][b.size()+1];
    for (int i = 0; i <= a.size(); i++)
        for (int j = 0; j <= b.size(); j++){
            if (i == 0 || j == 0)
                dp[i][j] = "";
            else if (a[i-1] == b[j-1])
                dp[i][j] = dp[i - 1][j - 1] + a[i-1];
            else
                dp[i][j] = cmp(dp[i-1][j], dp[i][j-1]);
        }
    return dp[a.size()][b.size()];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    int t, loop = 1;
    string a, b, ans;
    cin>>t;
    while(t--){
        cin>>a>>b;
        ans = lcs(a, b);
        if (ans.empty()) ans = ":(";
        cout<<"Case "<<(loop++)<<": "<<ans<<endl;
    }

    return 0;
}
