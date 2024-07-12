// Author: Simon Lindholm
// Modified by: Sahil Yasar
// Description: Fast integration using an adaptive Simpson's rule.
// Usage:
// double sphereVolume = quad(-1, 1, [](double x) {
// return quad(-1, 1, [\&](double y) {
// return quad(-1, 1, [\&](double z) {
// return x*x + y*y + z*z < 1; });});});
// Tested here:
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3973

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
#define endl '\n'

#define S(a,b) (f(a) + 4*f((a+b) / 2) + f(b)) * (b-a) / 6
template <class F>
double rec(F& f, double a, double b, double eps, double S){
	double c = (a + b) / 2;
	double S1 = S(a, c), S2 = S(c, b), T = S1 + S2;
	if (abs(T - S) <= 15 * eps || b - a < 1e-10)
		return T + (T - S) / 15;
	return rec(f, a, c, eps / 2, S1) + rec(f, c, b, eps / 2, S2);
}
template<class F>
double quad(double a, double b, F f, double eps = 1e-8){
	return rec(f, a, b, eps, S(a, b));
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);

    int w, d, a, k, i;
    double l, r, mid, ans, cur;
    while(cin>>w>>d>>a>>k){
        double p1[k+1], q1[k+1], p2[k+1], q2[k+1];
        for (i = 0; i <= k; ++i)
            cin>>p1[i];
        for (i = 0; i <= k; ++i)
            cin>>q1[i];
        for (i = 0; i <= k; ++i)
            cin>>p2[i];
        for (i = 0; i <= k; ++i)
            cin>>q2[i];

        auto f1 = [&](double x){
            double n = 0, d = 0, temp = 1;
            for (int i = 0; i <= k; ++i){
                n += p1[i]*temp;
                d += q1[i]*temp;
                temp *= x;
            }
            return max(n/d + mid + 1e-8, 0.0);
        };
        auto f2 = [&](double x){
            double n = 0, d = 0, temp = 1;
            for (int i = 0; i <= k; ++i){
                n += p2[i]*temp;
                d += q2[i]*temp;
                temp *= x;
            }
            return max(n/d + mid + 1e-8, 0.0);
        };

        ans = d, l = 0, r = d;
        while(abs(l-r) >= 1e-8){
            mid = (l+r)/2;
            cur = quad(0, w, f1);
            cur -= quad(0, w, f2);
            if (cur+1e-8 < a)
                l = mid;
            else
                ans = r = mid;
        }
        cout<<fixed<<setprecision(5)<<ans<<endl;
    }

    return 0;
}
