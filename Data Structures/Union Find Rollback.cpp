// Tested here:
// https://leetcode.com/problems/process-restricted-friend-requests/submissions/1166759301

#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    // namespace unionFindRollback{
        struct DSUr{
            vector<int> p;
            int comp; // No. of components
            stack<pair<int, int>> his;
            DSUr(int n): p(n, -1), comp(n){}
            void make() { p.push_back(-1); ++comp; }
            int size(int v) { return -p[find(v)]; }
            int find(int v) { return (p[v]<0)? v: find(p[v]); }
            void rollback(int t){
                t = min(t+t, (int)his.size());
                for (int i = 0; i < t; ++i, his.pop())
                    p[his.top().first] = his.top().second;
            }
            bool join(int a, int b){
                a = find(a), b = find(b);
                if (a == b) return false;
                if (p[a] > p[b]) swap(a, b);
                his.push(make_pair(a, p[a]));
                his.push(make_pair(b, p[b]));
                p[a] += p[b], p[b] = a, --comp;
                return true;
            }
        };
    // }
    // using namespace unionFindRollback;

    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {
        DSUr f(n);
        vector<bool> ans;
        for (auto& x: requests){
            f.join(x[0], x[1]);
            bool temp = true;
            for (auto& y: restrictions)
                if (f.find(y[0]) == f.find(y[1])){
                    temp = false;
                    break;
                }
            
            if (!temp)
                f.rollback(1);
            ans.push_back(temp);
        }
        return ans;
    }
};
