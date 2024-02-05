#include <iostream>
#include <vector>
using namespace std;
#define endl '\n'

namespace sparseTable{
    template <class T>
    struct sTable{
        vector<vector<T>> st;
        T (*f)(T, T);
        sTable(T a[], int n, T (*f)(T, T)): f(f){
          int LOG = 33 - __builtin_clz(n), i, j;
          st.assign(LOG, vector<T>(n));
          for (i = 0; i < n; ++i) st[0][i] = a[i];
          for (i = 1; i < LOG; ++i)
            for (j = 0; j+(1<<i)-1 < n; ++j)
              st[i][j] = f(st[i-1][j], st[i-1][j+(1<<(i-1))]);
        }
        T query(int l, int r){
          int k = 31 - __builtin_clz(r-l+1);
          return f(st[k][l], st[k][r-(1<<k)+1]);
        }
    };
}
using namespace sparseTable;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    int n, q, a, b, i;
    cin>>n>>q;
    int arr[n];
    for (i = 0; i < n; ++i)
      cin>>arr[i];
    sTable<int> rmq(arr, n, [](int a, int b){return min(a, b);});
    while(q--){
      cin>>a>>b;
      cout<<rmq.query(--a, --b)<<endl;
    }

    return 0;
}
