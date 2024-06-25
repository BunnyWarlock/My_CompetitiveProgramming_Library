// Author: Sahil Yasar
// Tested here:
// https://www.spoj.com/problems/KQUERY/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define endl '\n'

namespace mergeSortTree{
    template <class T>
    struct MStree{
        vector<vector<T>> arr;
        size_t N;

        void build(T a[], int v, int tl, int tr){
            if (tl == tr){
                arr[v].push_back(a[tl]);
                return;
            }
            int tm = (tl + tr) / 2;
            build(a, v+1, tl, tm);
            build(a, v+2*(tm-tl+1), tm+1, tr);

            int i = 0, j = 0;
            while(i < arr[v+1].size() && j < arr[v+2*(tm-tl+1)].size()){
                if (arr[v+1][i] < arr[v+2*(tm-tl+1)][j]) arr[v].push_back(arr[v+1][i++]);
                else arr[v].push_back(arr[v+2*(tm-tl+1)][j++]);
            }
            while(i < arr[v+1].size()) arr[v].push_back(arr[v+1][i++]);
            while(j < arr[v+2*(tm-tl+1)].size()) arr[v].push_back(arr[v+2*(tm-tl+1)][j++]);
        }
        MStree(T a[], int n){
            N = n;
            arr.assign(2*N-1, vector<T>());
            build(a, 0, 0, N-1);
        }

        T query(int v, int tl, int tr, int l, int r, T x){
            if (l > tr || r < tl)
                return T();
            if (l <= tl && r >= tr) // Returns number of elements <= x
                return distance(arr[v].begin(), upper_bound(arr[v].begin(), arr[v].end(), x));
            int tm = (tl + tr) / 2;
            return query(v+1, tl, tm, l, r, x) + query(v+2*(tm-tl+1), tm+1, tr, l, r, x);
        }
        T query(int l, int r, T x){
            return query(0, 0, N-1, l, r, x);
        }
    };
}
using namespace mergeSortTree;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, q, i, j, k;
    cin>>n;
    int a[n];
    for (i = 0; i < n; ++i)
        cin>>a[i];
    MStree<int> m(a, n);

    cin>>q;
    while(q--){
        cin>>i>>j>>k;
        --i, --j;
        cout<<(j-i+1) - m.query(i, j, k)<<endl;
    }

    return 0;
}
