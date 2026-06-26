#include <vector>
#include <algorithm>
using namespace std;

// Memoization

int solve(int i, int j, vector<vector<int>>& dp, vector<vector<int>>& grid) {
    if(i < 0 || j < 0 || grid[i][j] == 1) return 0;
    if(i == 0 && j == 0) return 1;

    if(dp[i][j] != -1) return dp[i][j];

    return dp[i][j] = solve(i - 1, j, dp, grid) + solve(i, j - 1, dp, grid);
}

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int n = obstacleGrid.size(), m = obstacleGrid[0].size();
    vector<vector<int>> dp(n, vector<int>(m, -1));

    return solve(n - 1, m - 1, dp, obstacleGrid);
}

// Tabulation 2D

int uniquePathsWithObstacles(vector<vector<int>>& grid) {
   int n = grid.size(), m = grid[0].size();
   vector<vector<int>> dp(n, vector<int>(m, 0));

   if (grid[0][0] == 1) return 0;
   dp[0][0] = 1;

   for (int i = 0; i < n; ++i) {
       for (int j = 0; j < m; ++j) {
           if (grid[i][j] == 1) {
               dp[i][j] = 0;
               continue;
           }

           if (i > 0)
               dp[i][j] += dp[i - 1][j];
            
           if (j > 0)
               dp[i][j] += dp[i][j - 1];
       }
   }
   return dp[n - 1][m - 1];
}

// Tabulation Space Optimized

int uniquePathsWithObstacles(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    vector<int> dp(m, 0);

    if (grid[0][0] == 1) return 0;
    dp[0] = 1;

    for (int i{}; i < n; ++i) {
        for (int j{}; j < m; ++j) {
            if (grid[i][j] == 1)
                dp[j] = 0;
             else if(j > 0) 
                dp[j] += dp[j-1];
        }
    }

    return dp[m - 1];
}