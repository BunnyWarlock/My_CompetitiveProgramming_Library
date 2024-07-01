// Author: Sahil Yasar
// Tested here:
// kth: https://www.spoj.com/problems/MKTHNUM/
// LTE: https://www.spoj.com/problems/KQUERY/
// sum: https://leetcode.com/problems/range-sum-query-immutable/description/ (Not actually tested)

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
#define endl '\n'

namespace waveletTree{
    template <class T>
    struct wavelet{
        vector<int> p;
        vector<T> s, rank;
        wavelet *left, *right;
        T maxVal;

        template <class D = T>
        void build(D* from, D* to, D lo, D hi){
            maxVal = hi;
            if (from >= to) return;
            D mid = (lo + hi) >> 1;
            auto f = [mid](D x){ return x <= mid; };
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
        wavelet(T a[], int n){
            vector<pair<T, int>> pairs(n);
            for (int i = 0; i < n; ++i) pairs[i] = {a[i], i};
            sort(pairs.begin(), pairs.end());
            int k = 0, temp[n];
            rank.push_back(pairs[0].first);
            for (int i = 0; i < n; ++i){
                if (i > 0 && pairs[i-1].first != pairs[i].first)
                    ++k, rank.push_back(pairs[i].first);
                temp[pairs[i].second] = k;
            }
            build<int>(temp, temp+n, 0, k);
        }

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
        T kth(int l, int r, int k){
            return rank[kth(l, r, k, 0, maxVal)];
        }

        //count of numbers in [l, r] Less than or equal to k
        int LTE(int l, int r, int k, int lo, int hi){
            if(l > r || k < lo) return 0;
            if(hi <= k) return r - l + 1;
            int lb = p[l], rb = p[r+1], mid = (lo + hi) >> 1;;
            return left->LTE(lb, rb-1, k, lo, mid) +
                   right->LTE(l-lb, r-rb, k, mid+1, hi);
        }
        int LTE(int l, int r, int k){
            auto itr = upper_bound(rank.begin(), rank.end(), k);
            int x = prev(itr) - rank.begin();
            return LTE(l, r, x, 0, maxVal);
        }

        //count of numbers in [l, r] equal to k
        int count(int l, int r, int k, int lo, int hi){
            if(l > r || k < lo || k > hi) return 0;
            if(lo == hi) return r - l + 1;
            int lb = p[l], rb = p[r+1], mid = (lo + hi) >> 1;
            if(k <= mid) return left->count(lb, rb-1, k, lo, mid);
            return right->count(l-lb, r-rb, k, mid+1, hi);
        }
        int count(int l, int r, int k){
            auto itr = upper_bound(rank.begin(), rank.end(), k);
            int x = prev(itr) - rank.begin();
            return count(l, r, x, 0, maxVal);
        }

        //sum of numbers in [l ,r] less than or equal to k
        T sum(int l, int r, int k, int lo, int hi){
            if(l > r or k < lo) return 0;
            if(hi <= k) return s[r+1] - s[l];
            int lb = p[l], rb = p[r+1], mid = (lo + hi) >> 1;
            return left->sum(lb, rb-1, k, lo, mid) +
                   right->sum(l-lb, r-rb, k, mid+1, hi);
        }

        // swap a[i-1] with a[i]
        void swapadjacent(int i, int lo, int hi){
            if(lo == hi) return;
            p[i] = p[i-1] + p[i+1] - p[i];
            s[i] = s[i-1] + s[i+1] - s[i];
            int mid = (lo + hi) >> 1;
            if(p[i+1]-p[i] == p[i]-p[i-1]){
                if(p[i]-p[i-1]) return left->swapadjacent(p[i], lo, mid);
                else return right->swapadjacent(i-p[i], mid+1, hi);
            }
        }
        void swapadjacent(int i){
            swapadjacent(i, 0, maxVal);
        }
    };
}
using namespace waveletTree;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, q, i, l, r, k;
    cin>>n>>q;
    int64_t a[n];
    for (i = 0; i < n; ++i)
        cin>>a[i];
    wavelet<int64_t> w(a, n);
    while(q--){
        cin>>l>>r>>k;
        --l, --r;
        cout<<w.kth(l, r, k)<<endl;
    }

    return 0;
}
