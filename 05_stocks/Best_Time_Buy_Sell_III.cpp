#include <vector>

// Memoization

int solve(int i, bool buy, int cap, std::vector<int>& prices, std::vector<std::vector<std::vector<int>>>& dp) {
    int n = prices.size();

    if(i == n || cap == 0) return 0;
    if(dp[i][buy][cap] != -1) return dp[i][buy][cap];

    int p{};
    if(buy) {
        p = std::max(solve(i+1, 0, cap, prices, dp) - prices[i], solve(i+1, buy, cap, prices, dp));
    } else {
        p = std::max(solve(i+1, 1, cap-1, prices, dp) + prices[i], solve(i+1, buy, cap, prices, dp));
    }
    
    return dp[i][buy][cap] = p;
}

int maxProfit(std::vector<int>& prices) {
    int n = prices.size();
    std::vector<std::vector<std::vector<int>>> dp(n, std::vector<std::vector<int>>(2, std::vector<int>(3, -1)));

    return solve(0, 1, 2, prices, dp);
}

// Tabulation

int maxProfit(std::vector<int>& prices) {
    int n = prices.size();
    std::vector<std::vector<std::vector<int>>> dp(n+1, std::vector<std::vector<int>>(2, std::vector<int>(3)));

    for(int i{n-1}; i >= 0; --i) {
        for(int buy{}; buy < 2; ++buy) {
            for(int cap{1}; cap < 3; ++cap) {
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

    return dp[0][1][2];
}

// Tabulation Space Optimized

int maxProfit(std::vector<int>& prices) {
    int n = prices.size();
    std::vector<std::vector<int>> dp(2, std::vector<int>(3));

    for(int i{n-1}; i >= 0; --i) {
        for(int buy{}; buy < 2; ++buy) {
            for(int cap{1}; cap < 3; ++cap) {
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

    return dp[1][2];
}

// State Machine

int maxProfit(std::vector<int>& prices) {
    int buy1{INT_MIN},
        sell1{},
        buy2{INT_MIN},
        sell2{};
    
    for(auto p : prices) {
        buy1 = std::max(buy1, -p);
        sell1 = std::max(sell1, buy1 + p);
        buy2 = std::max(buy2, sell1 - p);
        sell2 = std::max(sell2, buy2 + p);
    }
    
    return sell2;
}