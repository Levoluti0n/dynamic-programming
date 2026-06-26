#include <vector>
using namespace std;

// Memoization

class Solution {
    int solve(int i, vector<int>& nums, vector<int>& memo) {
        if (i < 0) return 0;

        if (memo[i] != -1)
            return memo[i];

        int rob = nums[i] + solve(i - 2, nums, memo);
        int skip = solve(i - 1, nums, memo);

        return memo[i] = max(rob, skip);
    }

public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<int> memo(n, -1);

        return solve(n - 1, nums, memo);
    }
};

// Tabulation

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        if (n == 1)
            return nums[0];

        vector<int> dp(n);

        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for (int i = 2; i < n; ++i)
            dp[i] = max(dp[i - 1], nums[i] + dp[i - 2]);

        return dp[n - 1];
    }
};


// Tabulation Space Optimized

class Solution {
public:
    int rob(vector<int>& nums) {
        int prev2 = 0;
        int prev1 = 0;

        for (int num : nums) {
            int curr = max(prev1, num + prev2);
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};


// House Robber II

class Solution {
    int robRange(vector<int>& nums, int left, int right) {
        int prev2 = 0;
        int prev1 = 0;

        for (int i = left; i <= right; ++i) {
            int curr = max(prev1, nums[i] + prev2);
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }

public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        if (n == 1)
            return nums[0];

        return max(
            robRange(nums, 0, n - 2),
            robRange(nums, 1, n - 1)
        );
    }
};