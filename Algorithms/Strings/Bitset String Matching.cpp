// Author: Sahil Yasar
// Tested here:
// https://codeforces.com/problemset/problem/914/F

#include <iostream>
#include <string>
#include <bitset>
using namespace std;
#define endl '\n'

const int MAX = 1e5 + 10;
bitset<MAX> mask[26];
bitset<MAX> ans;
string text;

void computeMask(){
    for (int i = 0; i < 26; ++i)
        mask[i].reset();
    for(int i = 0; i < text.size(); ++i)
        mask[text[i] - 'a'].set(i);
}

void updateMask(int i, char c){
    mask[text[i] - 'a'].reset(i);
    text[i] = c;
    mask[text[i] - 'a'].set(i);
}

int match(string& pattern){
    if(pattern.size() > text.size()) { return 0; }
    ans.set();
    for(int i = 0; i < pattern.size(); ++i) {
        int c = pattern[i] - 'a';
        ans &= (mask[c] >> i);
    }
    return ans.count();
}

int matchRange(string& pattern, int l, int r){
    if(r - l + 1 < pattern.size()) { return 0; }
    pattern = pattern;
    ans.set();
    for(int i = 0; i < pattern.size(); ++i)
        ans &= (mask[pattern[i] - 'a'] >> i);
    return (ans >> l).count() - (ans >> (r-pattern.size()+2)).count();
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int q, op, a, b, ans;
    char c;
    string p;
    cin>>text;
    computeMask();
    cin>>q;
    while(q--){
        cin>>op;
        if (op == 1){
            cin>>a>>c;
            updateMask(--a, c);
        }
        else{
            cin>>a>>b>>p;
            ans = matchRange(p, --a, --b);
            cout<<ans<<endl;
        }
    }

    return 0;
}
