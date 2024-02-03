#include <iostream>
#include <vector>
using namespace std;
#define endl '\n'

namespace segmentTree{
    template <class T>
    struct SEGtree{
        vector<T> arr, lazyAdd;
        vector<int> rn, lo, hi;
        vector<pair<T, bool>> lazySet;
        size_t N;
        T temp = -1e9-10;

        void build(T a[], int v, int tl, int tr){
            lo[v] = tl, hi[v] = tr;
            if (tl == tr)
                arr[v] = a[tl];
            else{
                int tm = (tl + tr) / 2;
                build(a, v+1, tl, tm);
                build(a, rn[v]=v+2*(tm-tl+1), tm+1, tr);
                arr[v] = max(arr[v+1], arr[rn[v]]);
            }
        }
        SEGtree(T a[], int N) : N(N){
            arr.resize(2*N-1);
            lazyAdd.assign(2*N-1, 0);
            lazySet.assign(2*N-1, {0, 0});
            rn.assign(2*N-1, 0);
            lo.assign(2*N-1, 0);
            hi.assign(2*N-1, 0);
            build(a, 0, 0, N-1);
        }

        void push(int v) {
            if (lazySet[v].second) {
                set(lo[v], hi[v], lazySet[v].first, v+1);
                set(lo[v], hi[v], lazySet[v].first, rn[v]);
                lazySet[v].second = false;
            }
            else if (lazyAdd[v]){
                add(lo[v], hi[v], lazyAdd[v], v+1);
                add(lo[v], hi[v], lazyAdd[v], rn[v]);
                lazyAdd[v] = 0;
            }
        }

        T query(int l, int r, int v = 0){
            if (l > hi[v] || r < lo[v]) return temp;
            if (l <= lo[v] && r >= hi[v]) return arr[v];
            push(v);
            return max(query(l, r, v+1), query(l, r, rn[v]));
        }

        void add(int l, int r, T x, int v = 0){
            if (l > hi[v] || r < lo[v]) return;
            if (l <= lo[v] && r >= hi[v]){
                if (lazySet[v].second) lazySet[v].first += x;
                else lazyAdd[v] += x;
                arr[v] += x;
            }
            else{
                push(v);
                add(l, r, x, v+1), add(l, r, x, rn[v]);
                arr[v] = max(arr[v+1], arr[rn[v]]);
            }
        }

        void set(int l, int r, T x, int v = 0){
            if (l > hi[v] || r < lo[v]) return;
            if (l <= lo[v] && r >= hi[v])
                lazySet[v] = {arr[v]=x, !(lazyAdd[v]=0)};
            else{
                push(v);
                set(l, r, x, v+1), set(l, r, x, rn[v]);
                arr[v] = max(arr[v+1], arr[rn[v]]);
            }
        }
    };
}
using namespace segmentTree;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    int n, q, l, r, i, u;
    cin>>n>>q;
    int64_t arr[n];
    for (i = 0; i < n; ++i)
      cin>>arr[i];

    SEGtree<int64_t> t(arr, n);
    while(q--){
      cin>>i;
      if (i == 1){
        cin>>l>>r>>u;
        --l, --r;
        t.add(l, r, u);
      }
      else{
        cin>>i;
        --i;
        cout<<t.query(i, i)<<endl;
      }
    }

    return 0;
}
