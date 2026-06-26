#include <vector>

// Memoization

bool solve(int i, int k, std::vector<int>& nums, std::vector<std::vector<int>>& dp) {
    if(k == 0) return true;
    if(i == 0) return (nums[i] == k);

    if(dp[i][k] != -1) return dp[i][k];

    return solve(i-1, k, nums, dp) || (k >= nums[i] && solve(i-1, k-nums[i], nums, dp));
}

bool equal_sum_subset(std::vector<int>& nums) {
    int total_sum{};
    for(auto num : nums) total_sum += num;

    if(total_sum&1) return false;
    std::vector<std::vector<int>> dp(nums.size(), std::vector<int>(total_sum/2+1, -1));

    return solve(nums.size()-1, total_sum/2, nums, dp);
}

// Tabulation

bool equal_sum_subset(std::vector<int>& nums) {
    int n = nums.size();

    int total_sum{};
    for(auto num : nums) total_sum += num;

    if(total_sum&1) return false;
    int k = total_sum/2;

    std::vector<std::vector<bool>> dp(n, std::vector<bool>(k+1));

    for(int i{}; i < n; ++i) dp[i][0] = true;
    if(nums[0] <= k) dp[0][nums[0]] = true;

    for(int i{1}; i < n; ++i) {
        for(int sum{1}; sum <= k; ++sum) {
            dp[i][sum] = dp[i-1][sum] || ((sum >= nums[i]) && dp[i-1][sum-nums[i]]);
        }
    }
    return dp[n-1][k];
}

// Tabulation Space Optimized

bool equal_sum_subset(std::vector<int>& nums) {
    int n = nums.size();
    int total_sum{};

    for(auto num : nums) total_sum += num;
    if(total_sum&1) return false;

    int k = total_sum/2;
    std::vector<bool> dp(k+1);

    dp[0] = true;
    for(int i{1}; i < n; ++i) {
        for(int j{k}; j >= nums[i]; --j) {
            dp[j] = dp[j] || dp[j-nums[i]];
        }
    }
    return dp[k];
}