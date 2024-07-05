// Author: Lukas Polacek
// Modified by: Sahil Yasar
// Tested here:
// https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/practice-problems/algorithm/mancunian-and-twin-permutations-d988930c/

#include <iostream>
#include <vector>
using namespace std;
#define endl '\n'

namespace fenwickTree{
    template <class T>
	struct FT {
		vector<T> bit;
		T (*combine)(T, T);
		T temp;

		FT(int n, T (*f)(T, T), T val){
			bit.resize(n, val);
			combine = f;
            temp = val;
		}

		// a[pos] += dif
		void update(int pos, T dif) {
			for (; pos < bit.size(); pos |= pos + 1)
				bit[pos] = combine(bit[pos], dif);
		}

		// queires in [0, pos]
		T query(int pos) {
			T res = temp;
			for (++pos; pos > 0; pos &= pos - 1)
				res = combine(res, bit[pos-1]);
			return res;
		}

		// Only use if combine(a, b) is a+b
		// min pos such that sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if sum is empty.
		int lower_bound(T sum) {
			if (sum <= 0) return -1;
			int pos = 0;
			for (int pw = 1 << 25; pw; pw >>= 1)
				if (pos + pw <= bit.size() && bit[pos + pw-1] < sum)
					pos += pw, sum -= bit[pos-1];
			return pos;
		}
	};
}
using namespace fenwickTree;

const int MAX = 1e5 + 10;
vector<int> ind[MAX], s[MAX], e[MAX];
int a[MAX], b[MAX], ans[MAX];
pair<int, int> queries[MAX];

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

	int n, q, i, temp, l1, r1, l2, r2;
    cin>>n;
    for (i = 1; i <= n; ++i){
        cin>>temp;
        a[temp] = i;
    }
    for (i = 1; i <= n; ++i)
        cin>>b[i];

    cin>>q;
    for (i = 0; i < q; ++i){
        cin>>l1>>r1>>l2>>r2;
        ans[i] = r1 - l1 + 1;
        queries[i] = {l1, r1};
        s[l2].push_back(i);
        e[r2].push_back(i);
    }

    FT<int> f(MAX, [](int a, int b){ return a+b; }, 0);
    for (i = 1; i <= n; ++i){
        for (auto& j: s[i])
            ans[j] += f.query(queries[j].second) - f.query(queries[j].first - 1);
        f.update(a[b[i]], 1);
        for (auto& j: e[i])
            ans[j] -= f.query(queries[j].second) - f.query(queries[j].first - 1);
    }

    for (i = 0; i < q; ++i)
        cout<<ans[i]<<endl;

    return 0;
}
