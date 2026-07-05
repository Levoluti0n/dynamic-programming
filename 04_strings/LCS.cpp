#include <vector>
#include <string>

// Memoization

int solve(int i, int j, std::string& s1, std::string& s2, std::vector<std::vector<int>>& dp) {
    if(i < 0 || j < 0) return 0;
    if(dp[i][j] != -1) return dp[i][j];

    if(s1[i] == s2[j]) return dp[i][j] = 1 + solve(i-1, j-1, s1, s2, dp);

    return dp[i][j] = std::max(solve(i, j-1, s1, s2, dp), solve(i-1, j, s1, s2, dp));
}

int lcs(std::string& s1, std::string& s2) {
    int n = s1.size(), m = s2.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(m, -1));

    return solve(n-1, m-1, s1, s2, dp);
}

// Tabulation

int lcs(std::string& s1, std::string& s2) {
    int n = s1.size(), m = s2.size();

    std::vector<std::vector<int>> dp(n+1, std::vector<int>(m+1, 0));

    for(int i{1}; i <= n; ++i) {
        for(int j{1}; j <= m; ++j) {
            if(s1[i-1] == s2[j-1]) dp[i][j] = 1 + dp[i-1][j-1];
            else dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
        }
    }

    return dp[n][m];
}

// Tabulation Space Optimized

int lcs(std::string& s1, std::string& s2) {
    int n = s1.size(), m = s2.size();
    std::vector<int> prev(m+1);

    for(int i{1}; i <= n; ++i) {
        std::vector<int> curr(m+1);

        for(int j{1}; j <= m; ++j) {
            if(s1[i-1] == s2[j-1]) curr[j] = 1 + prev[j-1];
            else curr[j] = std::max(prev[j], curr[j-1]);
        }

        prev = std::move(curr);
    }
    return prev[m];
}

// Tabulation Single Vector

int lcs(std::string &s1, std::string &s2) {
    int n = s1.size(), m = s2.size();

    std::vector<int> dp(m + 1, 0);

    for (int i = 1; i <= n; i++) {
        int prevDiag = 0;

        for (int j = 1; j <= m; j++) {
            int temp = dp[j];

            if (s1[i - 1] == s2[j - 1]) {
                dp[j] = 1 + prevDiag;
            } else {
                dp[j] = std::max(dp[j], dp[j - 1]);
            }

            prevDiag = temp;
        }
    }

    return dp[m];
}