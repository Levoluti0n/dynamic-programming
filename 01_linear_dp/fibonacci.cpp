#include <vector>

// Memoization

class Solution {
    int dfs(int n, std::vector<int>& memo) {
        if (n <= 1)
            return n;

        if (memo[n] != -1)
            return memo[n];

        return memo[n] = dfs(n - 1, memo) + dfs(n - 2, memo);
    }

public:
    int fib(int n) {
        std::vector<int> memo(n + 1, -1);
        return dfs(n, memo);    
    }
};

// Tabulation 1D

class Solution {
public:
    int fib(int n) {
        if (n <= 1)
            return n;

        std::vector<int> dp(n + 1);

        dp[0] = 0;
        dp[1] = 1;

        for (int i = 2; i <= n; ++i)
            dp[i] = dp[i - 1] + dp[i - 2];

        return dp[n];
    }
};

// Tabulation Space Optimized

class Solution {
public:
    int fib(int n) {
        if (n <= 1)
            return n;

        int prev2 = 0;
        int prev1 = 1;

        for (int i = 2; i <= n; ++i) {
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};