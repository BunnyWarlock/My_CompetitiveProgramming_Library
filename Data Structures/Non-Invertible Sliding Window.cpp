// Author: pasricha_dhruv
// Modified by: Sahil Yasar
// Source: https://codeforces.com/blog/entry/143351
// Tested here:
// https://cses.fi/problemset/task/3405

#include <iostream>
#include <stack>
using namespace std;
#define endl '\n'

// Augmented Stack for Aggregates
template <class T>
struct AggStack{
    stack<pair<T, T>> st;
    T (*combine)(T, T);
    T temp;
    AggStack(T (*f)(T, T), T val): combine(f), temp(val) {}
    void push(T val){
        T cur = ((st.empty())? combine(val, temp): combine(val, st.top().second));
        st.push(make_pair(val, cur));
    }
    void pop(){ st.pop(); }
    T agg(){ return st.top().second; }
    T top(){ return st.top().first; }
    bool empty(){ return st.empty(); }
};

// Aggregated Queue
template <class T>
struct AggQueue{
    AggStack<T> in, out;
    AggQueue(T (*f)(T, T), T val): in(f, val), out(f, val){}
    void push(T val){ in.push(val); }
    void transfer(){
        if (out.empty())
            while(!in.empty()){
                out.push(in.top());
                in.pop();
            }
    }
    void pop(){ transfer(); out.pop(); }
    T front(){ transfer(); return out.top(); }
    T query(){
        if (in.empty()) return out.agg();
        if (out.empty()) return in.agg();
        return in.combine(in.agg(), out.agg());
    }
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int64_t n, k, x, a, b, c, i, ans;
    cin>>n>>k>>x>>a>>b>>c;
    AggQueue<int64_t> w([](int64_t a, int64_t b){ return a|b; }, 0);
    for (i = 1; i < k; ++i){
        w.push(x);
        x = (a*x + b) % c;
    }
    ans = 0;
    for (; i <= n; ++i){
        w.push(x);
        ans ^= w.query();
        w.pop();
        x = (a*x + b) % c;
    }
    cout<<ans<<endl;

    return 0;
}
