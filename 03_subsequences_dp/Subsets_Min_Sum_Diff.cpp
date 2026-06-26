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
        (t >= nums[i] ? solve(i - 1, t - nums[i], nums, dp) : false);
}

int subsets_min_diff(vector<int>& nums) {
    int n = nums.size();
    int total_sum = accumulate(nums.begin(), nums.end(), 0);
    int k = total_sum;

    vector<vector<int>> dp(n, vector<int>(k / 2 + 1, -1));

    for (int t = 0; t <= k / 2; t++) {
        solve(n - 1, t, nums, dp);
    }

    int res = INT_MAX;
    for (int i = 0; i <= k / 2; i++) {
        if (dp[n - 1][i]) {
            res = min(res, k - 2 * i);
        }
    }

    return res;
}

// Tabulation

int subsets_min_diff(vector<int>& nums) {
    int n = nums.size();
    int total_sum = accumulate(nums.begin(), nums.end(), 0);
    int k = total_sum;

    vector<vector<bool>> dp(n, vector<bool>(k / 2 + 1, false));

    for(int i{}; i < n; ++i) dp[i][0] = true;
    if(k/2 >= nums[0]) dp[0][nums[0]] = true;
    
    for(int i{1}; i < n; ++i) {
        for(int target{1}; target <= k/2; ++target) {
            dp[i][target] = dp[i-1][target] || (target >= nums[i] && dp[i-1][target-nums[i]]);
        }
    }

    int res = INT_MAX;
    for (int i = 0; i <= k / 2; i++) {
        if (dp[n - 1][i]) {
            res = min(res, k - 2 * i);
        }
    }

    return res;
}

// Tabulation Space Optimized


int subsets_min_diff(vector<int>& nums) {
    int n = nums.size();
    int total_sum = accumulate(nums.begin(), nums.end(), 0);
    int k = total_sum;

    vector<bool> dp(k / 2 + 1, false);

    dp[0] = true;
    
    for(auto num : nums) {
        for(int target{k/2}; target >= num; --target) {
            dp[target] = dp[target] || dp[target-num];
        }
    }

    int res = INT_MAX;
    for (int i = 0; i <= k / 2; i++) {
        if (dp[i]) {
            res = min(res, k - 2 * i);
        }
    }

    return res;
}