#include <vector>
#include <string>

int minDistance(std::string& word1, std::string& word2) {
    int n = word1.size(), m = word2.size();
    std::vector<int> dp(m+1);
    for(int i{1}; i <= n; ++i) {
        int diag{};
        for(int j{1}; j <= m; ++j) {
            int tmp = dp[j];
            if(word1[i-1] == word2[j-1]) 
                dp[j] = 1 + diag;
            else
                dp[j] = std::max(dp[j], dp[j-1]);
            diag = tmp;
        }
    }
    
    return (n - dp[m]) + (m - dp[m]);
}