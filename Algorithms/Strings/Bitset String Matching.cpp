// Author: Sahil Yasar
// Tested here:
// https://codeforces.com/problemset/problem/914/F
// https://codeforces.com/problemset/problem/963/D

#include <iostream>
#include <string>
#include <bitset>
#include <vector>
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

vector<int> pos(string& pattern, int l, int r) {
    matchRange(pattern, l, r);
    vector<int> positions;
    for(int i = ans._Find_next(l-1); i < r-pattern.size()+2; i = ans._Find_next(i))
        positions.push_back(i);
    return positions;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int q, k, i, ans;
    string p;
    cin>>text;
    computeMask();
    cin>>q;
    while(q--){
        cin>>k>>p;
        vector<int> ind = pos(p, 0, (int)text.size()-1);
        if (ind.size() < k)
            cout<<-1<<endl;
        else{
            ans = text.size();
            for (i = 0; i <= ind.size()-k; ++i)
                ans = min(ans, ind[i+k-1]-ind[i]+1);
            ans += p.size()-1;
            cout<<ans<<endl;
        }
    }

    return 0;
}
