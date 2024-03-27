// Author: Sahil Yasar
// Tested here:
// https://www.spoj.com/problems/LKS/ [0-1 Knapsack v-1]
// https://atcoder.jp/contests/dp/tasks/dp_e [0-1 Knapsack v-2]
// https://lqdoj.edu.vn/problem/knapsack4 [0-1 Knapsack v-3]
// https://cses.fi/problemset/task/1634 [Unbounded Knapsack]

#include <iostream>
#include <cstring>
#include <numeric>
#include <vector>
#include <algorithm>
using namespace std;
#define endl '\n'

// Solution for small knapsack capacity
long long knapsack1(int w[], int v[], int& c, int& n){
    long long ans[c+1];
    memset(ans, 0, sizeof(ans));
    for (int i = 0; i < n; ++i)
        // for (int j = w[i]; j <= c; ++j) // Unbounded Knapsack
        for (int j = c; j >= w[i]; --j) // 0-1 Knapsack
            ans[j] = max(ans[j], ans[j-w[i]] + v[i]);
    return ans[c];
}

// Solution for small sum of value
long long knapsack2(int w[], int v[], int& c, int& n){
    int sum = accumulate(v, v+n, 0);
    long long ans[sum+1];
    memset(ans, 0x3f, sizeof(ans));
    ans[0] = 0;
    for (int i = 0; i < n; ++i)
        for (int j = sum; j >= v[i]; --j) // 0-1 Knapsack
            ans[j] = min(ans[j], ans[j-v[i]] + w[i]);
    for (int i = sum; i >= 0; --i)
        if (ans[i] <= c)
            return i;
    return 0;
}

struct node{
    long long value, weight, mask;
    node(long long m, long long v, long long w)
    : mask(m), value(v), weight(w) {}
};

void solve(int w[], int v[], long long c, int n, vector<node>& S){
    int lim = 1<<n;
    for (int mask = 0; mask < lim; ++mask){
        long long weight = 0, value = 0;
        for (int i = 0; i < n; ++i)
            if ((mask>>i)&1){
                weight += w[i];
                value += v[i];
                if (weight > c) break;
            }
        if (weight <= c)
            S.push_back(node(mask, value, weight));
    }
}

// Solution for small number of element
long long knapsack3(int w[], int v[], long long& c, int& n){
    int m = n/2;
    int wl[m], vl[m], wr[n-m], vr[n-m];
    for (int i = 0; i < m; ++i)
        wl[i] = w[i], vl[i] = v[i];
    for (int i = m; i < n; ++i)
        wr[i-m] = w[i], vr[i-m] = v[i];

    vector<node> Sl, Sr;
    solve(wl, vl, c, m, Sl);
    solve(wr, vr, c, n-m, Sr);
    sort(Sr.begin(), Sr.end(), [](node& a, node& b){
        return (a.weight != b.weight)? a.weight < b.weight: a.value < b.value;
    });
    long long maxval[Sr.size()];
    long long maxmask[Sr.size()];
    maxval[0] = Sr[0].value;
    maxmask[0] = Sr[0].mask;
    for (int i = 1; i < Sr.size(); ++i){
        maxval[i] = (maxval[i-1] < Sr[i].value)? Sr[i].value: maxval[i-1];
        maxmask[i] = (maxval[i-1] < Sr[i].value)? Sr[i].mask: maxmask[i-1];
    }

    long long res = 0, mask = 0;
    for (node& x: Sl){
        int l = 0, r = int(Sr.size()), mid;
        while(l+1 < r){
            mid = (l+r)/2;
            if (x.weight + Sr[mid].weight <= c)
                l = mid;
            else
                r = mid;
        }
        long long temp = maxval[l] + x.value;
        if (res < temp){
          res = temp;
          mask = x.mask | (maxmask[l] << m);
        }
    }
    return mask;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    long long n, c, i;
    cin>>n>>c;
    int w[n], v[n];
    for (i = 0; i < n; ++i)
      cin>>w[i]>>v[i];

    long long mask = knapsack3(w, v, c, *(new int(n)));
    cout<<__builtin_popcountll(mask)<<endl;
    for (i = 0; i < n; ++i)
      if ((mask>>i)&1)
        cout<<i+1<<" ";
    cout<<endl;

    return 0;
}
