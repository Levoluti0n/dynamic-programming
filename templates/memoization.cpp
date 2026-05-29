#include <vector>
using namespace std;

/*
========================================
DP TEMPLATE - MEMOIZATION (TOP-DOWN)

How to use:
1. Define state (function parameters)
2. Define dp table size
3. Write recursion + cache results
4. Handle base cases
========================================
*/

class Solution {
public:
    vector<int> dp;

    int solve(int i, vector<int>& nums) {

        if (i < 0) return 0;

        if (dp[i] != -1) return dp[i];

        int take = nums[i] + solve(i - 2, nums);
        int skip = solve(i - 1, nums);

        return dp[i] = max(take, skip);
    }

    int memo(vector<int>& nums) {
        int n = nums.size();
        dp.assign(n, -1);

        return solve(n - 1, nums);
    }
};