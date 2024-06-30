// Author: Sahil Yasar
// Tested here:
// https://www.spoj.com/problems/MKTHNUM/
// https://www.spoj.com/problems/KQUERY/

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
#define endl '\n'

namespace waveletTree{
    struct wavelet{
        vector<int> p;
        vector<int64_t> s;
        wavelet *left, *right;

        void build(int* from, int* to, int lo, int hi){
            if (from >= to) return;
            int mid = (lo + hi) >> 1;
            auto f = [mid](int x){ return x <= mid; };
            p.push_back(0); s.push_back(0);
            for (auto itr = from; itr != to; ++itr){
                p.push_back(p.back() + f(*itr));
                s.push_back(s.back() + (*itr));
            }
            if (lo == hi) return;
            auto pivot = stable_partition(from, to, f);
            left = new wavelet();
            left->build(from, pivot, lo, mid);
            right = new wavelet();
            right->build(pivot, to, mid+1, hi);
        }
        wavelet(){ left = right = NULL; }

        ~wavelet() {
          delete left;
          delete right;
        }

        // kth smallest element in [l, r]
        int kth(int l, int r, int k, int lo, int hi){
            if (l > r) return 0;
            if (lo == hi) return lo;
            int inLeft = p[r+1] - p[l];
            int lb = p[l], rb = p[r+1], mid = (lo + hi) >> 1;
            if (k <= inLeft) return left->kth(lb, rb-1, k, lo, mid);
            return right->kth(l-lb, r-rb, k-inLeft, mid+1, hi);
        }

        //count of numbers in [l, r] Less than or equal to k
        int LTE(int l, int r, int k, int lo, int hi){
            if(l > r || k < lo) return 0;
            if(hi <= k) return r - l + 1;
            int lb = p[l], rb = p[r+1], mid = (lo + hi) >> 1;;
            return left->LTE(lb, rb-1, k, lo, mid) +
                   right->LTE(l-lb, r-rb, k, mid+1, hi);
        }

        //count of numbers in [l, r] equal to k
        int count(int l, int r, int k, int lo, int hi){
            if(l > r || k < lo || k > hi) return 0;
            if(lo == hi) return r - l + 1;
            int lb = p[l], rb = p[r+1], mid = (lo + hi) >> 1;
            if(k <= mid) return left->count(lb, rb-1, k, lo, mid);
            return right->count(l-lb, r-rb, k, mid+1, hi);
        }

        //sum of numbers in [l ,r] less than or equal to k
        int sum(int l, int r, int k, int lo, int hi){
            if(l > r or k < lo) return 0;
            if(hi <= k) return s[r+1] - s[l];
            int lb = p[l-1], rb = p[r], mid = (lo + hi) >> 1;;
            return left->sum(lb, rb-1, k, lo, mid) +
                   right->sum(l-lb, r-rb, k, mid+1, hi);
        }

        // swap a[i] with a[i+1], if a[i]!=a[i+1] call swapadjacent(i)
        void swapadjacent(int i){
            if(lo == hi) return;
            b[i] = b[i-1] + b[i+1] - b[i];
            c[i] = c[i-1] + c[i+1] - c[i];
            if(b[i+1]-b[i] == b[i]-b[i-1]){
                if(b[i]-b[i-1]) return left->swapadjacent(b[i]);
                else return right->swapadjacent(i-b[i]);
            }
            return;
        }
    };

    template<class T>
    struct waveletS{
        wavelet w;
        map<int, T> m;
        map<T, int> rank;
        vector<T> arr;
        int maxVal;

        waveletS(T a[], int n): arr(n){
            for (int i = 0; i < n; ++i)
                arr[i] = a[i], rank[a[i]];
            sort(arr.begin(), arr.end());
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

        //count of numbers in [l, r] Less than or equal to k
        int LTE(int l, int r, int k){
            auto itr = upper_bound(arr.begin(), arr.end(), k);
            int x = rank[*prev(itr)];
            return w.LTE(l, r, x, 0, maxVal);
        }

        //count of numbers in [l, r] equal to k
        int count(int l, int r, int k){
            auto itr = upper_bound(arr.begin(), arr.end(), k);
            int x = rank[*prev(itr)];
            return w.count(l, r, x, 0, maxVal);
        }
    };
}
using namespace waveletTree;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, q, i, l, r, k, maxVal;
    cin>>n;
    int64_t a[n];
    for (i = 0; i < n; ++i)
        cin>>a[i];
    waveletS<int64_t> w(a, n);
    cin>>q;
    while(q--){
        cin>>l>>r>>k;
        --l, --r;
        cout<<r-l+1 - w.LTE(l, r, k)<<endl;
    }

    return 0;
}
