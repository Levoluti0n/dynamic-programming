#include <vector>

// Memoization

int solve(int i, int lb, std::vector<int>& values, std::vector<int>& weights, std::vector<std::vector<int>>& dp) {
    if(i == 0) {
        if(weights[i] <= lb) return values[i];
        return 0;
    }
    if(dp[i][lb] != -1) return dp[i][lb];
    return dp[i][lb] = std::max(solve(i-1, lb, values, weights, dp), (weights[i] <= lb ? solve(i-1, lb-weights[i], values, weights, dp) : 0));
}

int knapsack(std::vector<int>& weights, std::vector<int>& values, int lb) {
    int w = weights.size(), v = values.size();

    std::vector<std::vector<int>> dp(v, std::vector<int>(lb+1, -1));
    return solve(v-1, lb, values, weights, dp);
}

// Tabulation

int knapsack(std::vector<int>& weights, std::vector<int>& values, int lb) {
    int w = values.size();

    std::vector<std::vector<int>> dp(w+1, std::vector<int>(lb+1, 0));

    for(int weight{weights[0]}; weight <= lb; ++weight) dp[0][weight] = values[0];

    for(int i{1}; i <= w; ++i) {
        for(int curr{}; curr <= lb; ++curr) {
            dp[i][curr] = dp[i-1][curr];
            
            if(curr >= weights[i-1]) {
                dp[i][curr] = std::max(dp[i-1][curr], values[i-1] + dp[i-1][curr-weights[i-1]]);
            }
        }
    }
    return dp[w][lb];
}

// Tabulation Space Optimized

int knapsack(std::vector<int>& weights, std::vector<int>& values, int lb) {
    int w = values.size();

    std::vector<int> dp(lb+1, 0);

    for(int i{}; i < w; ++i) {
        for(int j{lb}; j >= weights[i]; --j) {
            dp[j] = std::max(dp[j], values[i] + dp[j-weights[i]]);
        }
    }
    return dp[lb];
}