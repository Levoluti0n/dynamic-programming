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

int knapsack(int W,
             std::vector<int>& wt,
             std::vector<int>& val) {
    int n = wt.size();

    std::vector<std::vector<int>>
        dp(n, std::vector<int>(W + 1, 0));

    for (int w = wt[0]; w <= W; ++w)
        dp[0][w] = val[0];

    for (int i = 1; i < n; ++i) {
        for (int w = 0; w <= W; ++w) {
            int notTake = dp[i - 1][w];

            int take = 0;
            if (wt[i] <= w)
                take = val[i] +
                       dp[i - 1][w - wt[i]];

            dp[i][w] = std::max(take, notTake);
        }
    }

    return dp[n - 1][W];
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