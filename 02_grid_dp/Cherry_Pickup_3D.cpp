#include <vector>
#include <algorithm>
using namespace std;

// Memoization

int solve(int i, int j1, int j2, vector<vector<int>>& grid, std::vector<std::vector<std::vector<int>>>& dp) {
    int n = grid.size(), m = grid[0].size();
    if(j1 < 0 || j1 >= m || j2 < 0 || j2 >= m) return 0;
    if(i == n) return 0;
    if(dp[i][j1][j2] != -1) return dp[i][j1][j2];
    
    int res = 0;
    for(int x1{-1}; x1 <= 1; ++x1) {
        for(int x2{-1}; x2 <= 1; ++x2) {
            if(j1 != j2) res = std::max(res, grid[i][j1] + grid[i][j2] + solve(i + 1, j1 + x1, j2 + x2, grid, dp));
            else res = std::max(res, grid[i][j2] + solve(i + 1, j1 + x1, j2 + x2, grid, dp));
        }
    }
    return dp[i][j1][j2] = res;
}

int cherryPickup(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    std::vector<std::vector<std::vector<int>>> dp(n, std::vector<std::vector<int>>(m, std::vector<int>(m, -1)));

    return solve(0, 0, m-1, grid, dp);
}

// Tabulation 3D

int cherryPickup(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    std::vector<std::vector<std::vector<int>>> dp(n, std::vector<std::vector<int>>(m, std::vector<int>(m)));
    for(int j1{}; j1 < m; ++j1) {
        for(int j2{}; j2 < m; ++j2) {
            if(j1 != j2) dp[n-1][j1][j2] = grid[n-1][j1];
            dp[n-1][j1][j2] += grid[n-1][j2];
        }
    }
    for(int i{n-2}; i >= 0; --i) {
        for(int j1{}; j1 < m; ++j1) {
            for(int j2{}; j2 < m; ++j2) { 
                
                int res = 0;
                for(int x1{-1}; x1 <= 1; ++x1) {
                    for(int x2{-1}; x2 <= 1; ++x2) {
                        int value{};
                        if(j1 != j2) value = grid[i][j1];
                        value += grid[i][j2];
                        if(j1 + x1 < 0 || j1 + x1 >= m || j2 + x2 < 0 || j2 + x2 >= m)
                            value = 0;
                        else
                            value += dp[i + 1][j1 + x1][j2 + x2];
                        
                        res = std::max(value, res);
                    }
                }   
                dp[i][j1][j2] = res;
            }
        }
    }
    return dp[0][0][m-1];
}

// Tabulation Space Optimized

int cherryPickup(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();

    vector<vector<int>> next(m, vector<int>(m, 0));
    vector<vector<int>> curr(m, vector<int>(m, 0));

    for(int j1{}; j1 < m; ++j1) {
        for(int j2{}; j2 < m; ++j2) {
            if(j1 != j2) next[j1][j2] = grid[n-1][j1];
            next[j1][j2] += grid[n-1][j2];
        }
    }
    
    for(int i{n-2}; i >= 0; --i) {
        for(int j1{}; j1 < m; ++j1) {
            for(int j2{}; j2 < m; ++j2) { 
                
                int res = 0;
                for(int x1{-1}; x1 <= 1; ++x1) {
                    for(int x2{-1}; x2 <= 1; ++x2) {
                        int value{};
                        if(j1 != j2) value = grid[i][j1];
                        value += grid[i][j2];
                        if(j1 + x1 < 0 || j1 + x1 >= m || j2 + x2 < 0 || j2 + x2 >= m)
                            value = 0;
                        else
                            value += next[j1 + x1][j2 + x2];
                        
                        res = std::max(value, res);
                    }
                }   
                curr[j1][j2] = res;
            }
        }
        next = curr;
    }
    return next[0][m-1];
}