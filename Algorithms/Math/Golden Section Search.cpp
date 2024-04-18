// Author: Ulf Lundstrom
// Description: A better version of Ternary Search.
// Time: O(log((b-a) / epsilon))
// Tested here:
// https://www.codechef.com/problems/AMCS03

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
#define endl '\n'

const int MAX = 1e5 + 10;
int s[MAX], d[MAX];
int n;

// Finds the minimum point of the function f which is unimodal in the interval [a,b]
double gss(double a, double b, double (*f)(double)) {
	double r = (sqrt(5)-1)/2, eps = 1e-8;
	double x1 = b - r*(b-a), x2 = a + r*(b-a);
	double f1 = f(x1), f2 = f(x2);
	while (b-a > eps)
		if (f1 < f2) { //change to > to find maximum
			b = x2; x2 = x1; f2 = f1;
			x1 = b - r*(b-a); f1 = f(x1);
		} else {
			a = x1; x1 = x2; f1 = f2;
			x2 = a + r*(b-a); f2 = f(x2);
		}
	return f(a);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int k, i;
    cin>>n>>k;
    for (i = 0; i < n; ++i)
        cin>>s[i]>>d[i];

    double ans = gss(0, k, [](double t){
        double mx, mn;
        mx = mn = s[0]*t + d[0];
        for (int i = 1; i < n; ++i){
            mx = max(mx, s[i]*t + d[i]);
            mn = min(mn, s[i]*t + d[i]);
        }
        return mx - mn;
    });
    cout<<setprecision(6)<<fixed<<ans<<endl;

    return 0;
}
