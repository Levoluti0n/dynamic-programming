#include <vector>
#include <string>

// Memoization

bool solve(int i, int j, std::string& s1, std::string& s2, std::vector<std::vector<int>>& dp) {
    if(i < 0 && j < 0) return true;
    if(i < 0) {
        for(int nj{}; nj <= j; ++nj) {
            if(s2[nj] != '*') return false;
        }
        return true;
    }
    if(j < 0) return false; 

    if(dp[i][j] != -1) return dp[i][j];

    if(s1[i] == s2[j] || s2[j] == '?') return dp[i][j] = solve(i-1, j-1, s1, s2, dp);

    if(s2[j] == '*') {
        return dp[i][j] = solve(i-1, j, s1, s2, dp) || solve(i, j-1, s1, s2, dp);
    }

    return false;
}

bool isMatch(std::string& s, std::string& p) {
    int n = s.size(), m = p.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(m, -1));

    return solve(n-1, m-1, s, p, dp);
}

// Tabulation

bool isMatch(std::string& s, std::string& p) {
    int n = s.size(), m = p.size();
    std::vector<std::vector<bool>> dp(n+1, std::vector<bool>(m+1));

    dp[0][0] = true;

    for(int j{1}; j <= m; ++j) {
        bool matched{true};
        for(int nj{1}; nj <= j; ++nj) {
            if(p[nj-1] != '*') {
                matched = false;
                break;
            }
        }
        dp[0][j] = matched;
    }

    for(int i{1}; i <= n; ++i) {
        for(int j{1}; j <= m; ++j) {
            if(s[i-1] == p[j-1] || p[j-1] == '?') dp[i][j] = dp[i-1][j-1];
            else if(p[j-1] == '*') {
                dp[i][j] = dp[i-1][j] || dp[i][j-1];
            }
        }
    }

    return dp[n][m];
}

// Tabulation Space Optimized

bool isMatch(std::string& s, std::string& p) {
    int n = s.size(), m = p.size();
    std::vector<bool> dp(m+1);

    dp[0] = true;

    for (int j = 1; j <= m; ++j) dp[j] = dp[j - 1] && p[j - 1] == '*';

    for(int i{1}; i <= n; ++i) {
        int diag = dp[0];
        dp[0] = false;
        
        for(int j{1}; j <= m; ++j) {
            int prev = dp[j];

            if(s[i-1] == p[j-1] || p[j-1] == '?') dp[j] = diag;
            else if(p[j-1] == '*') {
                dp[j] = dp[j] || dp[j-1];
            } else {
                dp[j] = false;
            }
            
            diag = prev;
        }
    }

    return dp[m];
}