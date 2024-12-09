// Author: Sahil Yasar

// #include <bits/stdc++.h>
#include <iostream>
using namespace std;
#define endl '\n'

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template<class T>
// using oset = tree<T, null_type, less<T>, rb_tree_tag,
//              tree_order_statistics_node_update>;
// template <class K, class V> using ht = gp_hash_table<K, V>;

template <class T1, class T2> ostream& operator<<(ostream& out, const pair<T1, T2> p)
{ return out<<'('<<p.first<<", "<<p.second<<")"; }
template <class ...Args> auto &print(const Args &...args)
{ return ((cerr<<args<<", "), ...)<<"\b\b)"<<endl; }
#define watch(...) if(true){cerr<<"("#__VA_ARGS__") = ("; print(__VA_ARGS__);}

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sz(x) (int)x.size()
#define f first
#define s second
#define read(arr) for(auto& x: arr) cin>>x
#define write(arr) for(auto& x: arr) cout<<x<<" "; cout<<endl
#define mem(x, n) memset(x, n, sizeof(x))
#define getUnique(x) sort(all(x)); x.erase(unique(all(x)), x.end());

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    

    return 0;
}
