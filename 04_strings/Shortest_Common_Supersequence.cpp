#include <vector>
#include <string>

std::string shortestCommonSupersequence(std::string& s1, std::string& s2) {
    int n = s1.size(), m = s2.size();
    std::vector<std::vector<int>> dp(n+1, std::vector<int>(m+1));

    for(int i{1}; i <= n; ++i) {
        for(int j{1}; j <= m; ++j) {
            if(s1[i-1] == s2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = std::max(dp[i][j-1], dp[i-1][j]);
        }
    }

    int k = n + m - dp[n][m];
    int i{n}, j{m};
    std::string res(k, '#');

    while(i && j) {
        if(s1[i-1] == s2[j-1]) {
            res[--k] = s1[i-1];
            --i;
            --j;
        } else if(dp[i][j-1] > dp[i-1][j]) {
            res[--k] = s2[j-1];
            --j;
        } else {
            res[--k] = s1[i-1];
            --i;
        }
    }

    while(i) res[--k] = s1[--i];
    while(j) res[--k] = s2[--j];
    
    return res;
}
