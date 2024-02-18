// Author: Sahil Yasar
// Tested here:
// https://open.kattis.com/problems/convexhull
// Description: The function outputs a polygon giving the convex hull of the input points
// This polygon does not contain any colinear edges, and is given in counterclockwise order.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define endl '\n'

typedef pair<int64_t, int64_t> pll;

vector<pll> convexHull(vector<pll> pts) {
	if (pts.size() <= 1) return pts;
	sort(pts.begin(), pts.end());
	vector<pll> h(pts.size()+1);
	auto cross = [](pll p, pll a, pll b){
	return (a.first-p.first)*(b.second-p.second) -
				(a.second-p.second)*(b.first-p.first);
	}; // Returns the cross product of vectors pa and pb
	int s = 0, t = 0, i;
	for (i = 2; i--; s = --t, reverse(pts.begin(), pts.end()))
		for (pll& p : pts) {
			while (t >= s + 2 && cross(h[t-2], h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    int64_t n, x, y, i;
    while(cin>>n, n){
      vector<pll> p(n);
      for (i = 0; i < n; ++i){
        cin>>x>>y;
        p[i] = {x, y};
      }

      vector<pll> ans = convexHull(p);
      cout<<ans.size()<<endl;
      for (i = 0; i < ans.size(); ++i)
        cout<<ans[i].first<<" "<<ans[i].second<<endl;
    }

    return 0;
}
