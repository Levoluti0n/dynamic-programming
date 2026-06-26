#include <vector>
#include <algorithm>
using namespace std;

// Memoization

int solve(int i, int j, int n, vector<vector<int>>& grid, vector<vector<int>>& dp) {
    if(j < 0 || j >= n) return 1e9;
    if(i == 0) {
        return grid[i][j];
    }
    if(dp[i][j] != 1e9) return dp[i][j];
    int up = solve(i-1, j, n, grid, dp);
    int up_left = solve(i-1, j-1, n, grid, dp);
    int up_right = solve(i-1, j+1, n, grid, dp);
    return dp[i][j] = grid[i][j] + std::min({up, up_left, up_right});
}

int minFallingPathSum(vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<vector<int>> dp(n, vector<int>(n, 1e9));
    int res = std::numeric_limits<int>::max();
    for(int i{}; i < n; ++i) {
        res = std::min(res, solve(n-1, i, n, matrix, dp));
    }
    return res;
}

// Tabulation 2D

int minFallingPathSum(vector<vector<int>>& grid) {
    int n = grid.size();
    vector<vector<int>> dp(n, vector<int>(n));

    for(int i{}; i < n; ++i) {
        dp[0][i] = grid[0][i];
    }

    for(int i{1}; i < n; ++i) {
        for(int j{}; j < n; ++j) {
            int up = dp[i-1][j];
            int l = (j > 0) ? dp[i-1][j-1] : INT_MAX;
            int r = (j < n-1) ? dp[i-1][j+1] : INT_MAX;
            dp[i][j] = grid[i][j] + std::min({up, r, l});
        }
    }
    
    return *min_element(dp[n-1].begin(), dp[n-1].end());
}

// Tabulation Space Optimized

int minFallingPathSum(vector<vector<int>>& grid) {
    int n = grid.size();
    vector<int> dp(n);

    for(int i{}; i < n; ++i) {
        dp[i] = grid[0][i];
    }

    for(int i{1}; i < n; ++i) {
        vector<int> curr(n);
        for(int j{}; j < n; ++j) {
            int l = (j > 0) ? dp[j-1] : INT_MAX;
            int r = (j < n-1) ? dp[j+1] : INT_MAX;
            curr[j] = grid[i][j] + std::min({dp[j], r, l});
        }
        dp = curr;
    }
    
    return *min_element(dp.begin(), dp.end());
}