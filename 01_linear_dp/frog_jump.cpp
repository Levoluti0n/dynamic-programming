#include <vector>

// Memoization

class Solution {
    int solve(int i, std::vector<int>& cost, std::vector<int>& memo) {
        if (i == 0)
            return 0;

        if (memo[i] != -1)
            return memo[i];

        int oneStep = solve(i - 1, cost, memo)
                      + std::abs(cost[i] - cost[i - 1]);

        int twoStep = INT_MAX;
        if (i > 1)
            twoStep = solve(i - 2, cost, memo)
                      + std::abs(cost[i] - cost[i - 2]);

        return memo[i] = std::min(oneStep, twoStep);
    }

public:
    int minCost(std::vector<int>& cost) {
        int n = cost.size();
        std::vector<int> memo(n, -1);
        return solve(n - 1, cost, memo);
    }
};

// Tabulation 1D

class Solution {
public:
    int minCost(std::vector<int>& cost) {
        int n = cost.size();
        std::vector<int> dp(n, 0);

        dp[0] = 0;

        for (int i = 1; i < n; ++i) {
            int oneStep = dp[i - 1] + std::abs(cost[i] - cost[i - 1]);

            int twoStep = INT_MAX;
            if (i > 1)
                twoStep = dp[i - 2] + std::abs(cost[i] - cost[i - 2]);

            dp[i] = std::min(oneStep, twoStep);
        }

        return dp[n - 1];
    }
};

// Tabulation Space Optimized

class Solution {
public:
    int minCost(std::vector<int>& cost) {
        int n = cost.size();
        if (n == 1)
            return 0;

        int prev2 = 0;
        int prev1 = 0;

        for (int i = 1; i < n; ++i) {
            int oneStep = prev1 + std::abs(cost[i] - cost[i - 1]);

            int twoStep = INT_MAX;
            if (i > 1)
                twoStep = prev2 + std::abs(cost[i] - cost[i - 2]);

            int curr = std::min(oneStep, twoStep);

            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};