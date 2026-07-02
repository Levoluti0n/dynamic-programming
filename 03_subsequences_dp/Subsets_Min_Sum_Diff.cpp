#include <vector>
#include <numeric>
using namespace std;

// Memoization

bool solve(int i, int t, vector<int>& nums, vector<vector<int>>& dp) {
    if (t == 0) return true;
    if (i == 0) return nums[0] == t;

    if (dp[i][t] != -1) return dp[i][t];

    return dp[i][t] =
        solve(i - 1, t, nums, dp) ||
        (t >= nums[i] && solve(i - 1, t - nums[i], nums, dp));
}

int subsets_min_diff(vector<int>& nums) {
    int n = nums.size();
    int total_sum = accumulate(nums.begin(), nums.end(), 0);
    int k = total_sum / 2;

    vector<vector<int>> dp(n, vector<int>(k + 1, -1));

    for (int t{k}; t >= 0; --t) {
        if(solve(n - 1, t, nums, dp))
            return total_sum - 2 * t;
    }

    return 0;
}

// Tabulation

int subsets_min_diff(vector<int>& nums) {
    int n = nums.size();
    int total = accumulate(nums.begin(), nums.end(), 0);
    int k = total / 2;

    vector<vector<bool>> dp(n, vector<bool>(k + 1, false));

    dp[0][0] = true;
    if (nums[0] <= k)
        dp[0][nums[0]] = true;

    for (int i = 1; i < n; ++i) {
        for (int t = 0; t <= k; ++t)
            dp[i][t] = dp[i - 1][t] || (t >= nums[i] && dp[i - 1][t - nums[i]]);
    }

    for (int t = k; t >= 0; --t) {
        if (dp[n - 1][t])
            return total - 2 * t;
    }

    return 0;
}

// Tabulation Space Optimized

int subsets_min_diff(vector<int>& nums) {
    int n = nums.size();
    int total_sum = accumulate(nums.begin(), nums.end(), 0);
    int k = total_sum/2;

    vector<bool> dp(k + 1, false);

    dp[0] = true;
    
    for(auto num : nums) {
        for(int target{k}; target >= num; --target) {
            dp[target] = dp[target] || dp[target-num];
        }
    }

    for (int t{k}; t >= 0; --t) {
        if (dp[t]) return total_sum - 2 * t;
    }

    return 0;
}