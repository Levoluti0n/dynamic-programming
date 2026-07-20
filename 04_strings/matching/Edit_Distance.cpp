#include <vector>
#include <string>

// Memoization

int solve(int i, int j, std::string& s1, std::string& s2, std::vector<std::vector<int>>& dp) {
    if(i < 0) return j + 1;
    if(j < 0) return i + 1;

    if(dp[i][j] != -1) return dp[i][j];

    if(s1[i] == s2[j]) return dp[i][j] = solve(i-1, j-1, s1, s2, dp);

    return dp[i][j] = std::min({
        1 + solve(i, j - 1, s1, s2, dp),
        1 + solve(i - 1, j, s1, s2, dp),
        1 + solve(i - 1, j - 1, s1, s2, dp)
    });
}

int minDistance(std::string& word1, std::string& word2) {
    int n = word1.size(), m = word2.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(m, -1));

    return solve(n - 1, m - 1, word1, word2, dp);
}

// Tabulation

int minDistance(std::string& s1, std::string& s2) {
    int n = s1.size(), m = s2.size();
    std::vector<std::vector<int>> dp(n+1, std::vector<int>(m+1));

    for(int i{0}; i <= n; ++i) dp[i][0] = i;
    for(int j{0}; j <= m; ++j) dp[0][j] = j;

    for(int i{1}; i <= n; ++i) {
        for(int j{1}; j <= m; ++j) {
            if(s1[i-1] == s2[j-1]) dp[i][j] = dp[i-1][j-1];
            else {
                dp[i][j] = 1 + std::min({
                    dp[i][j-1],
                    dp[i-1][j],
                    dp[i-1][j-1]
                });
            }
        }
    }

    return dp[n][m];
}

// Tabulation Space Optimized

int minDistance(std::string& s1, std::string& s2) {
    int n = s1.size(), m = s2.size();
    std::vector<int> dp(m+1);

    for(int j{0}; j <= m; ++j) dp[j] = j;

    for(int i{1}; i <= n; ++i) {
        int diag = i - 1; 
        dp[0] = i;
        for(int j{1}; j <= m; ++j) {
            int tmp = dp[j];
            if(s1[i-1] == s2[j-1]) dp[j] = diag;
            else {
                dp[j] = 1 + std::min({
                    dp[j-1],
                    dp[j],
                    diag
                });
            }
            diag = tmp;
        }
    }

    return dp[m];
}