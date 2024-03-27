// Author: Sahil Yasar
// Tested here:
// https://leetcode.com/problems/coin-change/description/

const int64_t INF = 1e15;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int64_t dp[amount+1];
        fill(dp, dp+amount+1, INF);
        dp[0] = 0;
        for (int i = 0; i < coins.size(); ++i)
            for (int j = coins[i]; j <= amount; ++j)
                dp[j] = min(dp[j], dp[j-coins[i]]+1);

        int64_t ans = dp[amount];
        if (ans >= INT_MAX) ans = -1;
        return ans;
    }
};
