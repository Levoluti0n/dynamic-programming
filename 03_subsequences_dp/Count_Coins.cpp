#include <vector>

// Memoization

int solve(int i, int t, std::vector<int>& nums, std::vector<std::vector<int>>& dp) {
    if(i == 0) {
        return (t%nums[i] == 0);
    }
    if(dp[i][t] != -1) return dp[i][t];

    return dp[i][t] = solve(i-1, t, nums, dp) + (t >= nums[i] ? solve(i, t-nums[i], nums, dp) : 0); 
}

int change(int amount, std::vector<int>& coins) {
    int n = coins.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(amount+1, -1));
    
    return solve(n-1, amount, coins, dp);
}

// Tabulation Space Optimized

int change(int amount, std::vector<int>& coins) {
    std::vector<unsigned long long> dp(amount + 1, 0);
    dp[0] = 1;

    for (int coin : coins) {
        for (int j = coin; j <= amount; j++) {
            dp[j] += dp[j - coin];
        }
    }
    
    return (int)dp[amount];
}