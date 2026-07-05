#include <vector>

// Memoization

int solve(int i, int w, std::vector<int>& nums, std::vector<int>& wt, std::vector<std::vector<int>>& dp) {
    if(i == 0) {
        return ((int)(w/wt[0])) * nums[0];
    }

    if(dp[i][w] != -1) return dp[i][w];

    int not_take = solve(i-1, w, nums, wt, dp);
    int take = INT_MIN;
    if(w >= wt[i]) take = nums[i] + solve(i, w-wt[i], nums, wt, dp);

    return dp[i][w] = std::max(not_take, take);
}

int unbounded_knapsack(std::vector<int>& wt, std::vector<int>& nums, int w) {
    int n = nums.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(w+1, -1));

    return solve(n-1, w, nums, wt, dp);
}

// Tabulation

int unbounded_knapsack(std::vector<int>& wt, std::vector<int>& nums, int lb) {
    int n = nums.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(lb+1));

    for(int w{wt[0]}; w <= lb; ++w) dp[0][w] = ((int)(w/wt[0])) * nums[0];

    for(int i{1}; i < n; ++i) {
        for(int w{}; w <= lb; ++w) {
            int notTake = dp[i - 1][w];
            int take = (w >= wt[i]) ? nums[i] + dp[i][w - wt[i]] : notTake;

            dp[i][w] = std::max(notTake, take);
        }
    }

    return dp[n-1][lb];
}

// Tabulation Space Optimized

int unbounded_knapsack(std::vector<int>& wt,
                       std::vector<int>& val,
                       int W) {
    int n = val.size();

    std::vector<int> dp(W + 1, 0);

    for (int w{wt[0]}; w <= W; ++w) {
        dp[w] = (w / wt[0]) * val[0];
    }

    for (int i = 1; i < n; ++i) {
        for (int w = wt[i]; w <= W; ++w) {
            dp[w] = std::max(dp[w],
                             val[i] + dp[w - wt[i]]);
        }
    }

    return dp[W];
}