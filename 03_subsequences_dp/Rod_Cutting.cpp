#include <vector>

// Memoization

int solve(int i, int n, std::vector<int>& nums, std::vector<std::vector<int>>& dp) {
    if(i == 0) return nums[i] * n;
    if(dp[i][n] != -1) return dp[i][n];

    return dp[i][n] = std::max(solve(i-1, n, nums, dp), (n >= i+1 ? nums[i] + solve(i, n-i-1, nums, dp) : 0));
}

int rod_cutting(std::vector<int>& prices, int n) {
    std::vector<std::vector<int>> dp(n, std::vector<int>(n+1, -1));
    return solve(n-1, n, prices, dp);
}

// Tabulation

int rod_cutting(std::vector<int>& prices, int n) {
    std::vector<std::vector<int>> dp(n, std::vector<int>(n+1, 0));
    
    for(int i{0}; i <= n; ++i) dp[0][i] = prices[0] * i;

    for(int i{1}; i < n; ++i) {
        for(int j{}; j <= n; ++j) {
            int not_take = dp[i-1][j];
            int take = 0;
            if(i+1 <= j)
                take = prices[i] + dp[i][j-i-1];
            dp[i][j] = std::max(take, not_take);
        }
    }
    return dp[n-1][n];
}

// Tabulation Space Optimized

int rod_cutting(std::vector<int>& prices, int n) {
    std::vector<int> dp(n+1, 0);
    
    for(int i{0}; i <= n; ++i) dp[i] = prices[0] * i;

    for(int i{1}; i < n; ++i) {
        for(int j{i+1}; j <= n; ++j) {
            dp[j] = std::max(dp[j], prices[i] + dp[j-i-1]);
        }
    }
    return dp[n];
}