#include <vector>
#include <string>

// Tabulation Space Optimized

int lcsubstring(std::string& s1, std::string& s2) {
    int n = s1.size(), m = s2.size();

    std::vector<int> dp(m+1);
    int res{};

    for(int i{1}; i <= n; ++i) {
        int prev_diag{};
        for(int j{1}; j <= m; ++j) {
            int tmp = dp[j];
            if(s1[i-1] == s2[j-1]) {
                dp[j] = prev_diag + 1;
                res = std::max(res, dp[j]);
            } else {
                dp[j] = 0;
            }
            prev_diag = tmp;
        }
    }
    
    return res;
}