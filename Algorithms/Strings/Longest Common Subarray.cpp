// Author: Sahil Yasar
// Tested here:
// https://leetcode.com/problems/maximum-length-of-repeated-subarray/description/

#include <cstring>

class Solution {
public:
    int lcs(vector<int>& A, vector<int>& B, int n, int m){
        int dp[m+1], i, j, prev, temp;
        memset(dp, 0, sizeof(dp));
        int ans = 0;
        for (i = n-1; i >= 0; i--){
            prev = 0;
            for (j = m-1; j >= 0; j--){
                temp = dp[j];
                if (A[i] == B[j]) {
                    dp[j] = prev + 1;
                    ans = max(ans, dp[j]);
                }
                else
                    dp[j] = 0;
                prev = temp;
            }
        }
        return ans;
    }

    int findLength(vector<int>& nums1, vector<int>& nums2) {
        return lcs(nums1, nums2, nums1.size(), nums2.size());
    }
};
