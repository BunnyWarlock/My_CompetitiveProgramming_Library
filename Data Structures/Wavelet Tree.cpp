// Author: Sahil Yasar
// Tested here:
// https://www.spoj.com/problems/MKTHNUM/

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
#define endl '\n'

namespace waveletTree{
    struct wavelet{
        vector<int> p;
        wavelet *left, *right;

        void build(int* from, int* to, int x, int y){
            if (from >= to) return;
            int mid = (x + y) >> 1;
            auto f = [mid](int e){ return e <= mid; };
            p.push_back(0);
            for (auto itr = from; itr != to; ++itr)
                p.push_back(p.back() + f(*itr));
            if (x == y) return;
            auto pivot = stable_partition(from, to, f);
            left = new wavelet();
            left->build(from, pivot, x, mid);
            right = new wavelet();
            right->build(pivot, to, mid+1, y);
        }
        wavelet(){ left = right = NULL; }

        ~wavelet() {
          delete left;
          delete right;
        }

        // kth smallest element in [l, r]
        int kth(int l, int r, int k, int x, int y){
            if (l > r) return 0;
            if (x == y) return x;
            int inLeft = p[r+1] - p[l];
            int lb = p[l], rb = p[r+1], mid = (x + y) >> 1;
            if (k <= inLeft) return this->left->kth(lb, rb-1, k, x, mid);
            return this->right->kth(l-lb, r-rb, k-inLeft, mid+1, y);
        }
    };

    template<class T>
    struct waveletS{
        wavelet w;
        map<int, T> m;
        int maxVal;

        waveletS(T a[], int n){
            map<T, int> rank;
            for (int i = 0; i < n; ++i) rank[a[i]];
            int k = 1, temp[n];
            for (auto& [x, y]: rank)
                m[k] = x, y = k++;
            for (int i = 0; i < n; ++i) temp[i] = rank[a[i]];
            maxVal = k;
            w.build(temp, temp+n, 0, maxVal);
        }

        // kth smallest element in [l, r]
        T kth(int l, int r, int k){
            return m[w.kth(l, r, k, 0, maxVal)];
        }
    };
}
using namespace waveletTree;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, q, i, l, r, maxVal;
    cin>>n>>q;
    int64_t a[n];
    for (i = 0; i < n; ++i)
        cin>>a[i];
    waveletS<int64_t> w(a, n);
    while(q--){
        cin>>l>>r>>i;
        --l, --r;
        cout<<w.kth(l, r, i)<<endl;
    }

    return 0;
}
