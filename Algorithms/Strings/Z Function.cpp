// Author: Sahil Yasar

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
#define endl '\n'

vector<int> zFunc(string s){
  vector<int> z(s.length());
  for (int i = 1, l = 0, r = 0; i < s.length(); ++i){
    if (i < r) z[i] = min(r-i, z[i-l]);
    for(; s[z[i]]==s[i+z[i]]; ++z[i]);
    if (i+z[i] > r)
      l = i, r = i+z[i];
  }
  return z;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    int ans, i, mx;
    string s;
    cin>>s;
    if (s.length() < 3){
      cout<<"Just a legend"<<endl;
      return 0;
    }
    vector<int> z = zFunc(s);
    if (z[1] == s.length()-1){
      cout<<s.substr(0, s.length()-2)<<endl;
      return 0;
    }
    vector<int> temp;
    map<int, int> freq;
    for (i = mx = 0; i < z.size(); ++i){
      if (i+z[i]==s.length())
        temp.push_back(z[i]);
      mx = max(mx, z[i]);
      ++freq[z[i]];
    }
    ans = -1;
    for (i = 0; i < temp.size(); ++i)
      if (mx > temp[i] || freq[temp[i]] > 1)
        ans = max(ans, temp[i]);
    if (ans == -1)
      cout<<"Just a legend"<<endl;
    else
      cout<<s.substr(0, ans)<<endl;;

    return 0;
}
