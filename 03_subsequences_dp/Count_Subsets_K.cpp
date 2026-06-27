#include <vector>

// Memoization

int solve(int i, int k, std::vector<int>& nums, std::vector<std::vector<int>>& dp) {
    if(k == 0) return 1;
    if(i == 0) return (nums[i] == k);

    if(dp[i][k] != -1) return dp[i][k];

    return dp[i][k] = solve(i-1, k, nums, dp) + (k >= nums[i] ? solve(i-1, k-nums[i], nums, dp) : 0);
}

int count_subsets_sum_k(std::vector<int>& nums, int k) {
    int n = nums.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(k+1, -1));
    return solve(n-1, k, nums, dp);
}

// Tabulation

int count_subsets_sum_k(std::vector<int>& nums, int k) {
    int n = nums.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(k+1, 0));
    
    for(int i{}; i < n; ++i) dp[i][0] = 1;
    if(nums[0] <= k) dp[0][nums[0]] = 1;

    for(int i{1}; i < n; ++i) {
        for(int sum{1}; sum <= k; ++sum) {
            dp[i][sum] = dp[i-1][sum] + (sum >= nums[i] ? dp[i-1][sum-nums[i]] : 0);
        }
    }

    return dp[n-1][k];
}

// Tabulation Space Optimized

int count_subsets_sum_k(std::vector<int>& nums, int k) {
    int n = nums.size();
    std::vector<int> dp(k+1, 0);

    dp[0] = 1;

    for(auto num : nums) {
        for(int sum{k}; sum >= num; --sum) {
            dp[sum] = dp[sum] + dp[sum-num];
        }
    }

    return dp[k];
}