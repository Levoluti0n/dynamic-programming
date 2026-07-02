#include <vector>
#include <numeric>

/*
    Required S1 - S2 = D s.t. S1 >= S2

    S1 - S2 = D
    TotalSum - S2 - S2 = D
    TotalSum - D = 2*S2
    (TotalSum - D) / 2 = S2

    Count subsets with sum (TotalSum - D) / 2 = S2
*/

// Memoization

int solve(int i, int k, std::vector<int>& nums, std::vector<std::vector<int>>& dp) {
    if(i == 0) {
        if(k == 0 && nums[i] == 0) return 2;
        if(k == 0 || k == nums[i]) return 1;
        return 0;
    }

    if(dp[i][k] != -1) return dp[i][k];

    return dp[i][k] = solve(i-1, k, nums, dp) + (k >= nums[i] ? solve(i-1, k-nums[i], nums, dp) : 0);
}

int count_subsets_sum_k(std::vector<int>& nums, int k) {
    int n = nums.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(k+1, -1));
    return solve(n-1, k, nums, dp);
}

int countPartitions(int n, int d, std::vector<int>& arr) {
    int total_sum{};
    for(auto num : arr) total_sum += num;

    if(total_sum - d < 0 || (total_sum - d) & 1) return false;

    return count_subsets_sum_k(arr, (total_sum - d) / 2);
}

// Tabulation

int count_subsets_sum_k(std::vector<int>& nums, int k) {
    int n = nums.size();

    std::vector<std::vector<int>> dp(n, std::vector<int>(k + 1, 0));

    if (nums[0] == 0)
        dp[0][0] = 2;
    else {
        dp[0][0] = 1;
        if (nums[0] <= k)
            dp[0][nums[0]] = 1;
    }

    for (int i = 1; i < n; ++i) {
        for (int t = 0; t <= k; ++t) {

            int notTake = dp[i - 1][t];
            int take = 0;

            if (nums[i] <= t)
                take = dp[i - 1][t - nums[i]];

            dp[i][t] = take + notTake;
        }
    }

    return dp[n - 1][k];
}

int countPartitions(int n, int d, std::vector<int>& arr) {
    int total_sum = std::accumulate(arr.begin(), arr.end(), 0);

    if (total_sum < d) return 0;
    if ((total_sum - d) % 2 != 0) return 0;

    int target = (total_sum - d) / 2;

    return count_subsets_sum_k(arr, target);
}

// Tabulation Space Optimized

int count_subsets_sum_k(std::vector<int>& nums, int k) {
    int n = nums.size();

    std::vector<int> dp(k+1, 0);

    if (nums[0] == 0)
        dp[0] = 2;
    else {
        dp[0] = 1;
        if (nums[0] <= k)
            dp[nums[0]] = 1;
    }

    for (int i = 1; i < n; ++i) {
        for (int t{k}; t >= nums[i]; --t) {
            dp[t] = dp[t] + dp[t - nums[i]];
        }
    }

    return dp[k];
}

int countPartitions(int n, int d, std::vector<int>& arr) {
    int total_sum = std::accumulate(arr.begin(), arr.end(), 0);

    if (total_sum < d) return 0;
    if ((total_sum - d) % 2 != 0) return 0;

    int target = (total_sum - d) / 2;

    return count_subsets_sum_k(arr, target);
}