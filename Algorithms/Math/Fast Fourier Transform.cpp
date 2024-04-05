// Author: Ludo Pulles, chilli, Simon Lindholm
// Modified by: Sahil Yasar
// Tested here:
// https://www.spoj.com/problems/POLYMUL/

#include <iostream>
#include <vector>
#include <complex>
using namespace std;
#define endl '\n'

typedef complex<double> C;
typedef vector<double> vd;
const long double PI = acos(-1.0L);

void fft(vector<C>& a) {
	int n = a.size(), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, PI / k);
		for (int i = k; i < 2*k; ++i) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	vector<int> rev(n);
	for (int i = 0; i < n; ++i) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	for (int i = 0; i < n; ++i) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) for (int j = 0; j < k; ++j) {
			C z = rt[j+k] * a[i+j+k];
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}

void ifft(vector<C>& x){
	for(auto& elem : x) elem = conj(elem);
    fft(x);
    for(auto& elem : x)
		(elem = conj(elem)) /= x.size();
}

vd conv(const vd& a, const vd& b) {
	if (a.empty() || b.empty()) return {};
	vd res(a.size() + b.size() - 1);
	int L = 32 - __builtin_clz(res.size()), n = 1 << L;
	vector<C> in(n), out(n);
	copy(a.begin(), a.end(), begin(in));
	for (int i = 0; i < b.size(); ++i) in[i].imag(b[i]);
	fft(in);
	for (C& x : in) x *= x;
	for (int i = 0; i < n; ++i) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	for (int i = 0; i < res.size(); ++i) res[i] = imag(out[i]) / (4 * n);
	return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

	int t, n, i;
	cin>>t;
	while(t--){
		cin>>n;
		vd a(n+1), b(n+1);
		for (i = 0; i <= n; ++i)
			cin>>a[i];
		for (i = 0; i <= n; ++i)
			cin>>b[i];
		vd ans = conv(a, b);
		for (i = 0; i < ans.size(); ++i)
			// Basically does integer FFT
			cout<<(long long)(round(ans[i]))<<" ";
		cout<<endl;


		// cin>>n;
		// ++n;
		// k = 1 << (32 - __builtin_clz(n-1));
		// k <<= 1;
		// vector<C> a(k), b(k);
		// for (i = 0; i < n; ++i){
		// 	cin>>j;
		// 	a[i] = j;
		// }
		// for (i = 0; i < n; ++i){
		// 	cin>>j;
		// 	b[i] = j;
		// }
		// 
		// fft(a);
		// fft(b);
		// for (i = 0; i < k; ++i)
		// 	a[i] *= b[i];
		// ifft(a);
		// for (i = 0; i < n+n-1; ++i)
		// 	// Basically does integer FFT
		// 	cout<<(long long)(round(a[i].real()))<<" ";
		// cout<<endl;
	}

    return 0;
}
