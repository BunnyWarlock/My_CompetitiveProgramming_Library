// Author: Stjepan Glavina
// Description: Finds the lexicographically smallest rotation of a string.
// Time: O(N)
// Usage: rotate(v.begin(), v.begin()+minRotation(v), v.end());
// Tested here:
// https://vjudge.net/problem/UVA-719/origin

#include <iostream>
#include <string>
using namespace std;
#define endl '\n'

int minRotation(string s) {
	int a=0, N=s.size(); s += s;
	for (int b = 0; b < N; ++b) for (int k = 0; k < N; ++k) {
		if (a+k == b || s[a+k] < s[b+k]) { b += max(0, k-1); break; }
		if (s[a+k] > s[b+k]) { a = b; break; }
	}
	return a;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

	int t;
    string s;
    cin>>t;
    while(t--){
        cin>>s;
        cout<<minRotation(s) + 1<<endl;
    }

    return 0;
}
