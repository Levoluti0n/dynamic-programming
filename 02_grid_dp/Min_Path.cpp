#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9;

// Memoization

int solve(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& dp) {
    if(i == 0 && j == 0) return grid[i][j];
    if(i < 0 || j < 0) return INF;

    if(dp[i][j] != -1) return dp[i][j];

    return dp[i][j] = grid[i][j] + min(solve(i-1, j, grid, dp), solve(i, j-1, grid, dp));
}

int min_sum_path(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> dp(n, vector<int>(m, -1));

    return solve(n-1, m-1, grid, dp);
}

// Tabultaion 2D

int min_sum_path(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> dp(n, vector<int>(m));

    for(int i{}; i < n; ++i) {
        for(int j{}; j < m; ++j) {
            if(i == 0 && j == 0) { dp[i][j] = grid[i][j]; continue; }
            
            int up = (i > 0) ? dp[i-1][j] : INF;
            int left = (j > 0) ? dp[i][j-1] : INF;
            dp[i][j] = grid[i][j] + min(up, left);
        }
    }
    return dp[n-1][m-1];
}

// Tabultaion Space Optmized

int min_sum_path(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    vector<int> dp(m);

    dp[0] = grid[0][0];
    for(int i{1}; i < m; ++i) {
        dp[i] = dp[i-1] + grid[0][i];
    }

    for(int i{1}; i < n; ++i) {
        dp[0] += grid[i][0];
        for(int j{1}; j < m; ++j) {
            dp[j] = grid[i][j] + min(dp[j], dp[j-1]);
        }
    }

    return dp[m-1];
}

// In Place

int min_sum_path(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();

    for(int i{}; i < n; ++i) {
        for(int j{}; j < m; ++j) {
            if (i == 0 && j == 0) continue;
            
            int left = (j > 0) ? grid[i][j-1] : INF;
            int up = (i > 0) ? grid[i-1][j] : INF;

            grid[i][j] += min(left, up);
        }
    }

    return grid[n-1][m-1];
}
