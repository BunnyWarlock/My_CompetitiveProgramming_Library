// Author: Stanford
// Solves a general linear maximization problem.
// The input is taken in the standard form for linear programs.
//
// Maximize c1.x1 + c2.x2 + ... + cn.xn
// Subject to:
// a11.x1 + a12.x2 + ... + a1n.xn <= b1
// a21.x1 + a22.x2 + ... + a2n.xn <= b2
//      ...
// am1.x1 + am2.x2 + ... + amn.xn <= bm
// x1, x2, ... , xn >= 0
//
// This can be rewritten in a matrix form, by setting:
// x = (x1, x2, ... , xn)^T
// c = (c1, c2, ... , cn)^T
// b = (b1, b2, ... , bn)^T
//     [ a11  a12  ...  a1n ]
// A = | a21  a22  ...  a2n |
//     |      ...           |
//     [ am1  am2  ...  amn ]
// With these definition we can rewrite the LP as
// Maximize c.x
// Subject to Ax <= b && x >= 0
//
// Minimizing c1.x1 + c2.x2 + ... + cn.xn is the same as maximizing -c1.x1 - c2.x2 - ... - cn.xn
// You can raplace a11.x1 + a12.x2 + ... + a1n.xn >= b1 by -a11.x1 - a12.x2 - ... - a1n.xn <= -b1
// An equality u = v is equivalent to the system of inequalities u <= v and u >= v.
// Read More: https://www.matem.unam.mx/~omar/math340/std-form.html
//
// Returns -inf if there is no solution, inf if there are arbitrarily good solutions, or the maximum value of c.x otherwise.
// The input vector is set to an optimal x (or in the unbounded case, an arbitrary solution fulfilling the constraints).
// Numerical stability is not guaranteed. For better performance, define variables such that x = 0 is viable.
// Time: O(NM * #pivots), where a pivot may be e.g. an edge relaxation. O(2^n) in the general case.
// Tested here:
// https://toph.co/p/not-linkin-park

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;
#define endl '\n'

typedef double T; // long double, Rational, double + mod<P>...
typedef vector<T> vd;
typedef vector<vd> vvd;

const T eps = 1e-8, inf = 1/.0;
#define MP make_pair
#define ltj(X) if(s == -1 || MP(X[j],N[j]) < MP(X[s],N[s])) s=j

struct LPSolver {
	int m, n;
	vector<int> N, B;
	vvd D;

	LPSolver(const vvd& A, const vd& b, const vd& c) :
		m(b.size()), n(c.size()), N(n+1), B(m), D(m+2, vd(n+2)) {
			for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j) D[i][j] = A[i][j];
			for (int i = 0; i < m; ++i) { B[i] = n+i; D[i][n] = -1; D[i][n+1] = b[i];}
			for (int j = 0; j < n; ++j) { N[j] = j; D[m][j] = -c[j]; }
			N[n] = -1; D[m+1][n] = 1;
		}

	void pivot(int r, int s) {
		T *a = D[r].data(), inv = 1 / a[s];
		for (int i = 0; i < m+2; ++i) if (i != r && abs(D[i][s]) > eps) {
			T *b = D[i].data(), inv2 = b[s] * inv;
			for (int j = 0; j < n+2; ++j) b[j] -= a[j] * inv2;
			b[s] = a[s] * inv2;
		}
		for (int j = 0; j < n+2; ++j) if (j != s) D[r][j] *= inv;
		for (int i = 0; i < m+2; ++i) if (i != r) D[i][s] *= -inv;
		D[r][s] = inv;
		swap(B[r], N[s]);
	}

	bool simplex(int phase) {
		int x = m + phase - 1;
		for (;;) {
			int s = -1;
			for (int j = 0; j < n+1; ++j) if (N[j] != -phase) ltj(D[x]);
			if (D[x][s] >= -eps) return true;
			int r = -1;
			for (int i = 0; i < m; ++i) {
				if (D[i][s] <= eps) continue;
				if (r == -1 || MP(D[i][n+1] / D[i][s], B[i])
				             < MP(D[r][n+1] / D[r][s], B[r])) r = i;
			}
			if (r == -1) return false;
			pivot(r, s);
		}
	}

	T solve(vd &x) {
		int r = 0;
		for (int i = 1; i < m; ++i) if (D[i][n+1] < D[r][n+1]) r = i;
		if (D[r][n+1] < -eps) {
			pivot(r, n);
			if (!simplex(2) || D[m+1][n+1] < -eps) return -inf;
			for (int i = 0; i < m; ++i) if (B[i] == -1) {
				int s = 0;
				for (int j = 1; j < n+1; ++j) ltj(D[i]);
				pivot(i, s);
			}
		}
		bool ok = simplex(1); x = vd(n);
		for (int i = 0; i < m; ++i) if (B[i] < n) x[B[i]] = D[i][n+1];
		return ok ? D[m][n+1] : inf;
	}
};


int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t, i;
    double a, b, c, d, r, x, y, z, ans;
    string s;
    cout<<fixed<<setprecision(3);
    cin>>t;
    while(t--){
        cin>>a>>b>>c>>d>>r;
        d = (d)? 1: -1;
        vd C = {a*d, b*d};
        vd B; vvd A;
        for (i = 0; i < 3; ++i){
            cin>>x>>y>>s>>z;
            if (s != ">="){
                B.push_back(z + (x+y)*r);
                A.push_back({x, y});
            }
            if (s != "<="){
                B.push_back(-z - (x+y)*r);
                A.push_back({-x, -y});
            }
        }
        A.push_back({1, 0});
        B.push_back(r+r);
        A.push_back({0, 1});
        B.push_back(r+r);

        vd x(2);
        ans = LPSolver(A, B, C).solve(x);
        ans = ans*d + c - (a+b)*r;
        if (isinf(ans))
            cout<<"No Solution"<<endl;
        else
            cout<<ans<<endl;
    }

    return 0;
}
