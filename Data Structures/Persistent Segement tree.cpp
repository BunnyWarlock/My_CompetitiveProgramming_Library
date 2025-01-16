// Author: Sahil Yasar
// Tested here:
// https://cses.fi/problemset/task/1734
// https://codeforces.com/blog/entry/117688?#comment-1225843
// https://cses.fi/problemset/task/1737/

#include <iostream>
#include <vector>
using namespace std;
#define endl '\n'

const int N = 2e5 + 10;
const int M = 1e7 + 10;
typedef int64_t T;

T arr[M];
int L[M], R[M], root[N];
size_t sz;
int nodes = 0, cnt = 0;
T val;
T (*f)(T, T);

void build(T a[], int v, int tl, int tr){
    if (tl == tr) arr[v] = a[tl];
    else{
        int tm = (tl + tr) / 2;
        build(a, L[v] = nodes++, tl, tm);
        build(a, R[v] = nodes++, tm+1, tr);
        arr[v] = f(arr[L[v]], arr[R[v]]);
    }
}
void PSEGtree(T a[], size_t n, T (*func)(T, T), T x){
    sz = n, f = func, val = x;
    build(a, root[cnt++] = nodes++, 0, sz-1);
}
void reset(){ nodes = cnt = 0; }

T query(int v, int l, int r, int tl, int tr){
    if (l > tr || r < tl) return val;
    if (l <= tl && r >= tr) return arr[v];
    int tm = (tl + tr) / 2;
    return f(query(L[v], l, r, tl, tm),
            query(R[v], l, r, tm+1, tr));
}
T query(int l, int r, int rt){
    return query(root[rt], l, r, 0, sz-1);
}

void update(int cur, int prev, int pos, T x, int tl, int tr){
    if (tl == tr) return void(arr[cur] = x);
    int tm = (tl + tr) / 2;
    if (pos <= tm){
        R[cur] = R[prev], L[cur] = nodes++;
        update(L[cur], L[prev], pos, x, tl, tm);
    }
    else{
        L[cur] = L[prev], R[cur] = nodes++;
        update(R[cur], R[prev], pos, x, tm+1, tr);
    }
    arr[cur] = f(arr[L[cur]], arr[R[cur]]);
}
int update(int pos, T x, int rt = -1){
    if (rt < 0) rt = cnt-1;
    update(root[cnt] = nodes++, root[rt], pos, x, 0, sz-1);
    return cnt++;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int64_t n, q, i, k, a, b;
    cin>>n>>q;
    int64_t t[n];
    for (i = 0; i < n; ++i)
        cin>>t[i];
    PSEGtree(t, n, [](int64_t x, int64_t y){ return x+y; }, 0);

    vector<int> rt(1, 0);
    while(q--){
        cin>>i;
        if (i == 1){
            cin>>k>>a>>b;
            --k, --a;
            rt[k] = update(a, b, rt[k]);
        }
        else if (i == 2){
            cin>>k>>a>>b;
            --k, --a, --b;
            cout<<query(a, b, rt[k])<<endl;
        }
        else{
            cin>>k;
            rt.push_back(rt[k-1]);
        }
    }

    return 0;
}
