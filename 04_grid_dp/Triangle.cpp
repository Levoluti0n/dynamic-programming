#include <vector>
#include <algorithm>
using namespace std;

// Memoization

int solve(int i, int j, vector<vector<int>>& grid, int n, vector<vector<int>>& dp) {
    if(i == n-1) return grid[i][j];

    if(dp[i][j] != -1) return dp[i][j];

    int d = solve(i+1, j, grid, n, dp);
    int dg = solve(i+1, j+1, grid, n, dp);

    return dp[i][j] = grid[i][j] + min(d, dg);
}

int min_path_triangle(vector<vector<int>>& triangle, int n) {
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return solve(0, 0, triangle, n, dp);
}

// Tabulation 2D

int min_path_triangle(vector<vector<int>>& triangle, int n) {
    vector<vector<int>> dp(n, vector<int>(n));
    
    for(int j{}; j < n; ++j) {
        dp[n-1][j] = triangle[n-1][j];
    }

    for(int i{n-2}; i >= 0; --i) {
        for(int j{}; j <= i; ++j) {
            dp[i][j] = triangle[i][j] + min(dp[i+1][j], dp[i+1][j+1]);
        }
    }

    return dp[0][0];
}

// Tabulation Space Optimized

int min_path_triangle(vector<vector<int>>& triangle, int n) {
    vector<int> dp(n);
    
    for(int j{}; j < n; ++j) {
        dp[j] = triangle[n-1][j];
    }

    for(int i{n-2}; i >= 0; --i) {
        for(int j{}; j <= i; ++j) {
            dp[j] = triangle[i][j] + min(dp[j], dp[j+1]);
        }
    }

    return dp[0];
}