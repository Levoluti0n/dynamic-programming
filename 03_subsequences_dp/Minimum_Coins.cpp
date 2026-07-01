#include <vector>

static constexpr int INF = 1e9;

// Memoization

int solve(int i, int k, std::vector<int>& nums, std::vector<std::vector<int>>& dp) {
    if(i == 0) {
        if(k % nums[i] == 0) return k / nums[i];
        return INF;
    }

    if(dp[i][k] != -1) return dp[i][k];

    return dp[i][k] = std::min(solve(i-1, k, nums, dp), (k >= nums[i] ? 1 + solve(i, k - nums[i], nums, dp) : INF));
}

int coinChange(std::vector<int>& nums, int amount) {
    int n = nums.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(amount+1, -1));

    int ans = solve(n-1, amount, nums, dp);
    
    return (ans >= INF) ? -1 : ans;;
}

// Tabulation

int coinChange(std::vector<int>& nums, int amount) {
    int n = nums.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(amount + 1));

    for(int t{}; t <= amount; ++t) {
        if(t % nums[0] == 0) dp[0][t] = t / nums[0];
        else dp[0][t] = INF;
    }

    for(int i{1}; i < n; ++i) {
        for(int sum{}; sum <= amount; ++sum) {
            int not_take = dp[i-1][sum];
            int take = INF;
            if(sum >= nums[i]) {
                take = 1 + dp[i][sum-nums[i]];
            }
            dp[i][sum] = std::min(take, not_take);
        }
    }
    return (dp[n-1][amount] >= INF) ? -1 : dp[n-1][amount];
}

// Tabulation Space Optimized

int coinChange(std::vector<int>& coins, int amount) {
    const int INF = amount + 1;
    std::vector<int> dp(amount + 1, INF);
    dp[0] = 0;

    for (int coin : coins) {
        for (int t = coin; t <= amount; ++t) {
            dp[t] = std::min(dp[t], dp[t - coin] + 1);
        }
    }
    
    return dp[amount] == INF ? -1 : dp[amount];
}
