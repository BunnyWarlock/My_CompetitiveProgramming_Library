#include <iostream>
#include <vector>
using namespace std;
#define endl '\n'

namespace unionFind{
    struct DSU{
        vector<int> p;
        int comp; // No. of components
        DSU(int n): p(n, -1), comp(n){}
        void make() { p.push_back(-1); ++comp; }
        int size(int v) { return -p[find(v)]; }
        int find(int v) { return (p[v]<0)? v: p[v]=find(p[v]); }
        bool join(int a, int b){
          a = find(a), b = find(b);
          if (a == b) return false;
          if (p[a] > p[b]) swap(a, b);
          p[a] += p[b], p[b] = a, --comp;
          return true;
        }
    };
}
using namespace unionFind;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    int n, m, q, i;
    cin>>n>>m;
    DSU d(n);
    int a[m], b[m];
    for (i = 0; i < m; ++i)
      cin>>a[i]>>b[i];

    vector<bool> temp(m, true);
    cin>>q;
    int c[q], ans[q];
    for (i = 0; i < q; ++i){
      cin>>c[i];
      temp[--c[i]] = false;
    }
    for (i = 0; i < m; ++i)
      if (temp[i])
        d.join(a[i]-1, b[i]-1);

    for (i = q-1; i >= 0; --i){
      ans[i] = d.comp;
      d.join(a[c[i]]-1, b[c[i]]-1);
    }
    for (i = 0; i < q; ++i)
      cout<<ans[i]<<" ";
    cout<<endl;

    return 0;
}
