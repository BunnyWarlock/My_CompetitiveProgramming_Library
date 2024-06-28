// Author: Ludo Pulles, chilli, Simon Lindholm
// Modified by: Sahil Yasar
// Tested here:
// https://www.spoj.com/problems/POLYMUL/
// https://cses.fi/problemset/task/1753
// https://judge.yosupo.jp/problem/wildcard_pattern_matching

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

// Returns an array of \sum_{j=0}^{m-1}(P[j] - T[i + j])^2
// where m is the length of s2
vector<int> stringMatch(string& s1, string& s2){
    long long i, j, cur, val;
    vd a(s1.length()), b(s2.length()), temp;
    for (j = 0; j < s1.length(); ++j)
        a[j] = s1[j] - 'a' + 1;
    val = 0;
    for (j = 0; j < s2.length(); ++j){
        b[j] = s2[s2.length()-1-j] - 'a' + 1;
        val += b[j]*b[j];
    }
    temp = conv(a, b);

    cur = 0;
    vector<int> ans;
    for (i = 0; i < s2.length(); ++i)
        cur += a[i]*a[i];
    ans.push_back(val + cur - 2*(long long)round(temp[i-1]));
    for ( ; i < s1.length(); ++i){
        cur -= a[i-s2.length()]*a[i-s2.length()];
        cur += a[i]*a[i];
        ans.push_back(val + cur - 2*(long long)round(temp[i]));
    }
    return ans;
}

// Returns an array of \sum_{j=0}^{m-1}P[j]T[i+j](P[j] - T[i + j])^2
// where m is the length of w
vector<int> stringMatchWildcard(string& t, string& w, char c = '?'){
    long long i, temp;
    vd t1(t.size()), t2(t.size()), t3(t.size());
    for (i = 0; i < t.size(); ++i){
        t1[i] = (t[i]!=c) * (t[i]-'a'+1);
        t2[i] = t1[i] * t1[i];
        t3[i] = t2[i] * t1[i];
    }
    vd w1(w.size()), w2(w.size()), w3(w.size());
    for (i = 0; i < w.size(); ++i){
        w1[i] = (w[w.size()-1-i]!=c) * (w[w.size()-1-i]-'a'+1);
        w2[i] = w1[i] * w1[i];
        w3[i] = w2[i] * w1[i];
    }

    vd t1w3 = conv(t1, w3);
    vd t2w2 = conv(t2, w2);
    vd t3w1 = conv(t3, w1);
    vector<int> ans;
    for (i = w.size()-1; i < t.size(); ++i){
        temp = (long long)round(t1w3[i]) - 2*(long long)round(t2w2[i]) + (long long)round(t3w1[i]);
        ans.push_back(temp);
    }
    return ans;
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

	/*string s1, s2;
    cin>>s1>>s2;
    vector<int> ans = stringMatch(s1, s2);
    int cnt = 0;
    for (auto x: ans)
	cnt += (x == 0);
	cout<<cnt<<endl;*/

    return 0;
}
