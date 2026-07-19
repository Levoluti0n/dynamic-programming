#include <vector>
#include <string>

// Memoization

int solve(int i, int j, std::string& s1, std::string& s2, std::vector<std::vector<int>>& dp) {
    if(j < 0) return 1;
    if(i < 0) return 0;

    if(dp[i][j] != -1) return dp[i][j];

    if(s1[i] == s2[j]) {
        return dp[i][j] = solve(i-1, j-1, s1, s2, dp) + solve(i-1, j, s1, s2, dp);
    }
    return dp[i][j] = solve(i-1, j, s1, s2, dp);
}

int numDistinct(std::string& s, std::string& t) {
    int n = s.size(), m = t.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(m, -1));

    return solve(n-1, m-1, s, t, dp);
}

// Tabulation

int numDistinct(std::string& s, std::string& t) {
    int n = s.size(), m = t.size();
    std::vector<std::vector<unsigned long long>> dp(n+1, std::vector<unsigned long long>(m+1));
    for(int i{}; i <= n; ++i) dp[i][0] = 1;

    for(int i{1}; i <= n; ++i) {
        for(int j{1}; j <= m; ++j) {
            dp[i][j] = dp[i-1][j];
            if(s[i-1] == t[j-1]) dp[i][j] += dp[i-1][j-1];
        }
    }

    return dp[n][m];
}

// Tabulation Space Optimized

int numDistinct(std::string& s, std::string& t) {
    int n = s.size(), m = t.size();
    std::vector<unsigned long long> dp(m+1);
    dp[0] = 1;

    for(int i{1}; i <= n; ++i) {
        for(int j{m}; j > 0; --j) {
            if(s[i-1] == t[j-1]) dp[j] += dp[j-1];
        }
    }

    return dp[m];
}