#include <iostream>
#include <vector>
using namespace std;
#define endl '\n'

namespace segmentTree{
    template <class T>
    struct SEGtree{
        vector<T> arr;
        size_t N;
        T (*combine)(T, T);
        T temp;

        void build(T a[], int v, int tl, int tr){
            if (tl == tr){
                arr[v] = a[tl];
                return;
            }
            int tm = (tl + tr) / 2;
            build(a, v+1, tl, tm);
            build(a, v+2*(tm-tl+1), tm+1, tr);
            arr[v] = combine(arr[v+1], arr[v+2*(tm-tl+1)]);
        }
        SEGtree(T a[], int n, T (*f)(T, T), T val){
            N = n;
            arr.resize(2*N-1);
            combine = f;
            temp = val;
            build(a, 0, 0, N-1);
        }

        T query(int v, int tl, int tr, int l, int r){
            if (l > tr || r < tl)
                return temp;
            if (l <= tl && r >= tr)
                return arr[v];
            int tm = (tl + tr) / 2;
            return combine(query(v+1, tl, tm, l, r),
                   query(v+2*(tm-tl+1), tm+1, tr, l, r));
        }
        T query(int l, int r){
            return query(0, 0, N-1, l, r);
        }

        void update(int v, int tl, int tr, int pos, T new_val){
            if (tl == tr){
                arr[v] = new_val;
                return;
            }
            int tm = (tl + tr) / 2;
            if (pos <= tm) update(v+1, tl, tm, pos, new_val);
            else update(v+2*(tm-tl+1), tm+1, tr, pos, new_val);
            arr[v] = combine(arr[v+1], arr[v+2*(tm-tl+1)]);
        }
        void update(int pos, T new_val){
            update(0, 0, N-1, pos, new_val);
        }



        int lower_bound(int v, int tl, int tr, T k) {
            if (k > arr[v])
                return -1;
            if (tl == tr)
                return tl;
            int tm = (tl + tr) / 2;
            if (arr[v+1] >= k)
                return lower_bound(v+1, tl, tm, k);
            else
                return lower_bound(v+2*(tm-tl+1), tm+1, tr, k-arr[v+1]);
        }
        int lower_bound(T k){
          return lower_bound(0, 0, N-1, k);
        }
    };
}
using namespace segmentTree;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    int n, q, l, r, i;
    cin>>n>>q;
    int64_t arr[n];
    for (i = 0; i < n; ++i)
      cin>>arr[i];

    SEGtree<int64_t> t(arr, n, [](int64_t a, int64_t b)->int64_t{return a^b;}, 0);
    while(q--){
      cin>>l>>r;
      --l, --r;
      cout<<t.query(l, r)<<endl;
    }

    return 0;
}
