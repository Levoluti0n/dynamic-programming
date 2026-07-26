#include <vector>

// Memoization

int solve(int i, int buy, std::vector<int>& prices, std::vector<std::vector<int>>& dp) {
    if(i == prices.size()) return 0;
    if(dp[i][buy] != -1) return dp[i][buy];

    int p{};
    if(buy) {
        p = std::max(solve(i+1, 0, prices, dp) - prices[i], solve(i+1, 1, prices, dp));
    } else {
        p = std::max(solve(i+1, 1, prices, dp) + prices[i], solve(i+1, 0, prices, dp));
    }

    return dp[i][buy] = p;
}

int maxProfit(std::vector<int>& prices) {
    int n = prices.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(2, -1));

    return solve(0, 1, prices, dp);
}

// Tabulation

int maxProfit(std::vector<int>& prices) {
    int n = prices.size();
    std::vector<std::vector<int>> dp(n+1, std::vector<int>(2));
    dp[n][0] = dp[n][1] = 0;

    for(int i{n-1}; i >= 0; --i) {
        for(int buy{0}; buy < 2; ++buy) {
            int p{};
            if(buy) {
                p = std::max(dp[i+1][0] - prices[i], dp[i+1][1]);
            } else {
                p = std::max(dp[i+1][1] + prices[i], dp[i+1][0]);
            }
            dp[i][buy] = p;
        }
    }
    return dp[0][1];
}

// Tabulation Space Optimized

int maxProfit(std::vector<int>& prices) {
    int n = prices.size();
    std::vector<int> dp(2);

    for(int i{n-1}; i >= 0; --i) {
        for(int buy{0}; buy < 2; ++buy) {
            int p{};
            
            if(buy) {
                p = std::max(dp[0] - prices[i], dp[1]);
            } else {
                p = std::max(dp[1] + prices[i], dp[0]);
            }

            dp[buy] = p;
        }
    }

    return dp[1];
}