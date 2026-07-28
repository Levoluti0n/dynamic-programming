#include <vector>

// Memoization

class Solution {
    int solve(int i, int buy, int k, std::vector<int>& prices, std::vector<std::vector<std::vector<int>>>& dp) {
        int n = prices.size();

        if(i == n || !k) return 0;
        if(dp[i][buy][k] != -1) return dp[i][buy][k];

        int p{};
        if(buy) {
            p = std::max(solve(i+1, 0, k, prices, dp) - prices[i], solve(i+1, 1, k, prices, dp));
        } else {
            p = std::max(solve(i+1, 1, k-1, prices, dp) + prices[i], solve(i+1, 0, k, prices, dp));
        }
        return dp[i][buy][k] = p;
    }
public:
    int maxProfit(int k, std::vector<int>& prices) {
        int n = prices.size();
        std::vector<std::vector<std::vector<int>>> dp(n, std::vector<std::vector<int>>(2, std::vector<int>(k+1, -1)));

        return solve(0, 1, k, prices, dp);
    }
};

// Tabulation

class Solution {
public:
    int maxProfit(int k, std::vector<int>& prices) {
        int n = prices.size();
        std::vector<std::vector<std::vector<int>>> dp(n+1, std::vector<std::vector<int>>(2, std::vector<int>(k+1)));

        for(int i{n-1}; i >= 0; --i) {
            for(int buy{}; buy < 2; ++buy) {
                for(int cap{k}; cap > 0; --cap) {
                    int p{};
                    if(buy) {
                        p = std::max(dp[i+1][0][cap] - prices[i], dp[i+1][1][cap]);
                    } else {
                        p = std::max(dp[i+1][1][cap-1] + prices[i], dp[i+1][0][cap]);
                    }
                    dp[i][buy][cap] = p;
                }
            }
        }

        return dp[0][1][k];
    }
};

// Tabulation Space Optimized

class Solution {
public:
    int maxProfit(int k, std::vector<int>& prices) {
        int n = prices.size();
        std::vector<std::vector<int>> dp(2, std::vector<int>(k+1));

        for(int i{n-1}; i >= 0; --i) {
            for(int buy{}; buy < 2; ++buy) {
                for(int cap{k}; cap > 0; --cap) {
                    int p{};
                    if(buy) {
                        p = std::max(dp[0][cap] - prices[i], dp[1][cap]);
                    } else {
                        p = std::max(dp[1][cap-1] + prices[i], dp[0][cap]);
                    }
                    dp[buy][cap] = p;
                }
            }
        }

        return dp[1][k];
    }
};