#include <vector>

// Memoization

bool solve(int i, int target,
           const std::vector<int>& nums,
           std::vector<std::vector<int>>& dp) {
    
    if (target == 0)
        return true;
    if (i == 0)
        return nums[0] == target;
    
    if (dp[i][target] != -1)
        return dp[i][target];

    return dp[i][target] =
        solve(i - 1, target, nums, dp) ||
        (nums[i] <= target &&
         solve(i - 1, target - nums[i], nums, dp));
}

bool subsetSumEqualsK(const std::vector<int>& nums, int K) {
    int n = nums.size();
    std::vector<std::vector<int>> dp(
        n, std::vector<int>(K + 1, -1));
        
    return solve(n - 1, K, nums, dp);
}

// Tabulation 2D

bool subsetSumEqualsK(const std::vector<int>& nums, int K) {
    int n = nums.size();
    std::vector<std::vector<bool>> dp(n, std::vector<bool>(K + 1, false));

    for(int i{}; i < n; ++i)
        dp[i][0] = true;
    
    if(nums[0] <= K)
        dp[0][nums[0]] = true;
    
    for(int i{1}; i < n; ++i) {
        for(int sum{1}; sum <= K; ++sum) {
            bool not_take = dp[i-1][sum];
            bool take = false;
            
            if(sum >= nums[i]) {
                take = dp[i-1][sum-nums[i]];
            }

            dp[i][sum] = take || not_take;
        }
    }
    
    return dp[n-1][K];
}

// Tabulation Space Optimized

bool subsetSumEqualsK(const std::vector<int>& nums, int K) {
    std::vector<bool> dp(K + 1, false);
    dp[0] = true;
    
    for(auto num : nums) {
        for(int sum{K}; sum >= num; --sum) {
            dp[sum] = dp[sum] || dp[sum-num];
        }
    }
    
    return dp[K];
}


