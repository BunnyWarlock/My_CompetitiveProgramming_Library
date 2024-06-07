// Author: Sahil Yasar
// Tested here:
// https://leetcode.com/problems/longest-increasing-subsequence/description/

class Solution {
public:
    // namespace fenwickTree{
        template <class T>
        struct FT {
            vector<T> bit;
            T (*combine)(T, T);
            T temp;

            FT(int n, T (*f)(T, T), T val){
                bit.resize(n, val);
                combine = f;
                temp = val;
            }

            // a[pos] += dif
            void update(int pos, T dif) {
                for (; pos < bit.size(); pos |= pos + 1)
                    bit[pos] = combine(bit[pos], dif);
            }

            // queires in [0, pos]
            T query(int pos) {
                T res = temp;
                for (++pos; pos > 0; pos &= pos - 1)
                    res = combine(res, bit[pos-1]);
                return res;
            }
        };
    // }
    // using namespace fenwickTree;

    vector<int> LIS(vector<int>& arr){
        int n = arr.size();
        int ind[n];
        iota(ind, ind+n, 0);
        sort(ind, ind+n, [&](int a, int b){
            if (arr[a] == arr[b])
                return a > b;
            return arr[a] < arr[b];
        });

        vector<int> ans(n);
        FT<int> temp(n, [](int a, int b){ return max(a, b); }, 0);
        for (auto& i: ind){
            ans[i] = temp.query(i) + 1;
            temp.update(i, ans[i]);
        }
        return ans;
    }

    int lengthOfLIS(vector<int>& nums) {
        vector<int> ans = LIS(nums);
        return *max_element(ans.begin(), ans.end());
    }
};
