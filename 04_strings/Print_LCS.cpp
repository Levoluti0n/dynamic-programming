#include <vector>
#include <string>

// Tabulation

std::string lcs(std::string& s1, std::string& s2) {
    int n = s1.size(), m = s2.size();

    std::vector<std::vector<int>> dp(n+1, std::vector<int>(m+1, 0));

    for(int i{1}; i <= n; ++i) {
        for(int j{1}; j <= m; ++j) {
            if(s1[i-1] == s2[j-1]) dp[i][j] = 1 + dp[i-1][j-1];
            else dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
        }
    }

    int k = dp[n][m];

    std::string res(k, '#');
    int i = n, j = m;
    while(i && j) {
        if(s1[i-1] == s2[j-1]) {
            res[--k] = s1[i-1];
            --i;
            --j;
        } else if(dp[i][j-1] > dp[i-1][j]) {
            --j;
        } else {
            --i;
        }
    }

    return res;
}