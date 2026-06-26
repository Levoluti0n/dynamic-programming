#include <vector>
#include <algorithm>
using namespace std;

// Memoization

int solve(int i, int j, vector<vector<int>>& dp) {
    if(i == 0 && j == 0) return 1;
    if(i < 0 || j < 0) return 0;

    if(dp[i][j] != -1) return dp[i][j];

    return dp[i][j] = solve(i-1, j, dp) + solve(i, j-1, dp);
}

int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, -1));
    return solve(m-1, n-1, dp);
}

// Tabulation 2D

int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = 1;
    
    for(int i{}; i < m; ++i) {
        for(int j{}; j < n; ++j) {
            if(i == 0 && j == 0) continue;

            int up = (i > 0) ? dp[i-1][j] : 0;
            int left = (j > 0) ? dp[i][j-1] : 0;
            dp[i][j] = up + left;
        }
    }

    return dp[m-1][n-1];
}

// Tabulation Space Optimized

int uniquePaths(int m, int n) {
    vector<int> dp(n, 1);

    for(int i{1}; i < m; ++i) {
        for(int j{1}; j < n; ++j) {
            dp[j] += dp[j-1];
        }
    }
    return dp[n-1];
}

// Combinatorics

int uniquePaths(int m, int n) {
    long long res = 1;

    int N = m + n - 2;
    int r = min(m - 1, n - 1);

    for (int i = 1; i <= r; ++i) {
        res = res * (N - r + i) / i;
    }

    return (int)res;
}