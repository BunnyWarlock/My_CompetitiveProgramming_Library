// Author: Sahil Yasar
// Tested here:
// https://www.codechef.com/problems/MARCAPS

#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

template <class T>
vector<T> derangement(vector<T> a){
    int n = a.size();
    int ind[n], maxf, cur, i;
    iota(ind, ind+n, 0);
    sort(ind, ind+n, [&](int i, int j){
        return a[i] < a[j];
    });
    maxf = cur = 1;
    for (i = 1; i < n; ++i, ++cur)
        if (a[ind[i]] != a[ind[i-1]]){
            maxf = max(maxf, cur);
            cur = 0;
        }
    maxf = max(maxf, cur);
    if (maxf+maxf > n)
        return {};
    vector<T> ans(n);
    for (i = 0; i < n; ++i)
        ans[ind[(i+maxf)%n]] = a[ind[i]];
    return ans;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t, n, i;
    cin>>t;
    while(t--){
        cin>>n;
        vector<int> a(n);
        for (i = 0; i < n; ++i)
            cin>>a[i];
        vector<int> ans = derangement(a);
        if (ans.empty())
            cout<<"No"<<endl;
        else{
            cout<<"Yes"<<endl;
            for (i = 0; i < n; ++i)
                cout<<ans[i]<<" ";
            cout<<endl;
        }
    }

    return 0;
}
