// Author: Sahil Yasar
// Tested here:
// https://lightoj.com/problem/summing-up-powers-ii

#include <iostream>
#include <vector>
using namespace std;
#define endl '\n'

typedef long long ll;

template<class T, ll MOD = 0x7FFFFFFFFFFFFFFF>
struct Matrix {
	typedef Matrix M;
  vector<vector<T>> d;
  int N;
  Matrix(int N): N(N), d(N, vector<T>(N, T())) {}
	M& operator=(const M& other) {
		if (this != &other) {
			this->N = other.N;
			this->d = other.d;
		}
		return *this;
	}
	M operator*(const M& m) const {
		M a(N);
		for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
  			for (int k = 0; k < N; ++k)
          a.d[i][j] = (a.d[i][j] + d[i][k]*m.d[k][j]) % MOD;
		return a;
	}
	vector<T> operator*(const vector<T>& vec) const {
		vector<T> ret(N);
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        ret[i] = (ret[i] + d[i][j] * vec[j]) % MOD;
		return ret;
	}
  M operator+(const M& m) const {
		M a(N);
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        a.d[i][j] = (d[i][j] + m.d[i][j]) % MOD;
		return a;
	}
  M addI() const {
    M a(*this);
    for (int i = 0; i < N; ++i)
      ++a.d[i][i];
    return a;
  }
	M operator^(ll p) const {
		M a(N), b(*this);
		for (int i = 0; i < N; ++i)
      a.d[i][i] = 1;
		while (p) {
			if (p&1) a = a*b;
			b = b*b;
			p >>= 1;
		}
		return a;
	}
};

using mat = Matrix<int, 10>;
mat solve(mat& m, ll k){
  if (k == 1) return m;
  if (k&1) return solve(m, k-1) + (m^k);
  return (m^(k/2)).addI() * solve(m, k/2);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    int t, n, k, i, j, loop = 1;
    cin>>t;
    while(t--){
      cin>>n>>k;
      mat m(n);
      for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
          cin>>m.d[i][j];
      mat ans = solve(m, k);
      cout<<"Case "<<(loop++)<<":"<<endl;
      for (i = 0; i < n; ++i){
        for (j = 0; j < n; ++j)
          cout<<ans.d[i][j];
        cout<<endl;
      }
    }

    return 0;
}
