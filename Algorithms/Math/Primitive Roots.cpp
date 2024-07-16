// Author: Sahil Yasar
// Tested here:
// https://atcoder.jp/contests/agc047/tasks/agc047_c

#include <iostream>
#include <vector>
#include <complex>
using namespace std;
#define endl '\n'

typedef long long ll;
ll powMod(ll x, ll p, ll m){
  ll ans = 1;
  x %= m;
  if (!x) return 0;
  while(p){
    if (p&1)
      ans = (ans*x)%m;
    p = p>>1;
    x = (x*x)%m;
  }
  return ans;
}

int generator(int p){
    vector<int> fact;
    int phi = p-1,  n = phi;
    for (int i=2; i*i<=n; ++i)
        if (n % i == 0) {
            fact.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1) fact.push_back(n);

    for (int res = 2; res <= p; ++res){
        bool ok = true;
        for (int i = 0; i < fact.size() && ok; ++i)
            ok &= powMod(res, phi / fact[i], p) != 1;
        if (ok) return res;
    }
    return -1;
}


const int P = 200003;
const int G = generator(P);
int dlog[P];

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
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll n, i, j, ans;
    for (i = 0; i < P; ++i)
        dlog[powMod(G, i, P)] = i;
    cin>>n;
    vector<int> a;
    for (i = 0; i < n; ++i){
        cin>>j;
        if (j) a.push_back(dlog[j]);
    }

    // Arr has the frequency of the sum of all pairs of a
    vd freq(P, 0);
    for (i = 0; i < a.size(); ++i)
        ++freq[a[i]];
    vd temp = conv(freq, freq);
    vector<ll> arr(temp.size());
    for (i = 0; i < temp.size(); ++i)
        arr[i] = (long long)(round(temp[i]));
    for (i = 0; i < freq.size(); ++i)
        arr[i+i] -= freq[i];
    for (i = 0; i < arr.size(); ++i)
        arr[i] >>= 1;

    ans = 0;
    for (i = 0; i < arr.size(); ++i)
        ans += arr[i]*powMod(G, i, P);
    cout<<ans<<endl;

    return 0;
}
